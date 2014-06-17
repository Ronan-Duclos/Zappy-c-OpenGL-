/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_take_item.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmansour <dmansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/14 19:47:23 by dmansour          #+#    #+#             */
/*   Updated: 2014/06/14 20:32:05 by dmansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>
#include <libft.h>

void			take_item(t_env *e, int cs)
{
	char		*item;
	int			resource;
	int			player_x;
	int			player_y;

	item = e->users[cs]->player.acts[e->users[cs]->player.cur_aread].cmd;
	player_x = e->users[cs]->player.x;
	player_y = e->users[cs]->player.y;
	if ((resource = str_to_type(item)) == -1)
		tmp_to_bc(&e->users[cs]->buf_write, "KO", 1);
	else
	{
		if (e->map[player_x][player_y].ground[resource] == 0)
			tmp_to_bc(&e->users[cs]->buf_write, "KO", 1);
		else
		{
			e->map[player_x][player_y].ground[resource]--;
			e->users[cs]->player.inv[resource]++;
			tmp_to_bc(&e->users[cs]->buf_write, "OK", 1);
		}
	}
}
