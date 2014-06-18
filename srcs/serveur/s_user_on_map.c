/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_user_on_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/16 21:11:03 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/18 22:02:56 by rbernand         ###   ########.fr       */
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
	e->map[x][y].ground[_player]++;
	if (e->map[x][y].player == NULL)
		e->map[x][y].player = e->users[cs];
	else
	{
		tmp = e->map[x][y].player;
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
	e->map[x][y].ground[_player]--;
	tmp = e->map[x][y].player;
	if (tmp->sock == cs)
		e->map[x][y].player = e->map[x][y].player->next;
	else
	{
		while (tmp->next->sock != cs)
			tmp = tmp->next;
		me = tmp->next;
		tmp->next = me->next;
		me->next = NULL;
	}
}
