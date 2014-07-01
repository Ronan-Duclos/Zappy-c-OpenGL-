/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_user_on_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/16 21:11:03 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/25 23:30:30 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>

void	put_user_on_map(t_env *e, int cs)
{
	int		x;
	int		y;
	t_user	*tmp;

	x = e->users[cs]->player.x;
	y = e->users[cs]->player.y;
	e->map[y][x].ground[_player]++;
	if (e->map[y][x].player == NULL)
		e->map[y][x].player = e->users[cs];
	else
	{
		tmp = e->map[y][x].player;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = e->users[cs];
	}
	e->users[cs]->next = NULL;
}

void	remove_user_on_map(t_env *e, int cs)
{
	int		x;
	int		y;
	t_user	*tmp;
	t_user	*me;

	x = e->users[cs]->player.x;
	y = e->users[cs]->player.y;
	e->map[y][x].ground[_player]--;
	tmp = e->map[y][x].player;
	if (tmp && tmp->sock == cs)
		e->map[y][x].player = e->map[y][x].player->next;
	else
	{
		while (tmp != NULL && tmp->next != NULL && tmp->next->sock != cs)
			tmp = tmp->next;
		if (tmp)
		{
			me = tmp->next;
			if (me != NULL)
			{
				tmp->next = me->next;
				me->next = NULL;
			}
		}
	}
}
