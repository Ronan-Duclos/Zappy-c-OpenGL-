/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_drop_item.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmansour <dmansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/14 19:47:23 by dmansour          #+#    #+#             */
/*   Updated: 2014/06/23 18:44:43 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>

void			drop_item(t_env *e, int cs)
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
		if (e->users[cs]->player.inv[resource] == 0)
			tmp_to_bc(&e->users[cs]->buf_write, "KO", 1);
		else
		{
			e->map[player_x][player_y].ground[resource]++;
			e->users[cs]->player.inv[resource]--;
			tmp_to_bc(&e->users[cs]->buf_write, "OK", 1);
		}
	}
	gfx_send_npc(e, cs, gfx_pin);
	gfx_send_map(e, player_x, player_y, gfx_bct);
}

void			gfx_drop_item(t_env *e, int cs)
{
	char		*item;
	int			resource;

	item = e->users[cs]->player.acts[e->users[cs]->player.cur_aread].cmd;
	resource = str_to_type(item);
	if (resource < 0)
		return ;
	gfx_send_act(e, cs, gfx_pdr, resource);
}
