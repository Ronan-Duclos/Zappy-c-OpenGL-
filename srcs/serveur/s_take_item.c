/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_take_item.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmansour <dmansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/14 19:47:23 by dmansour          #+#    #+#             */
/*   Updated: 2014/06/25 23:29:33 by rduclos          ###   ########.fr       */
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
		tmp_to_bc(&e->users[cs]->buf_write, "ko", 1);
	else
	{
		if (e->map[player_y][player_x].ground[resource] > 0)
		{
			e->map[player_y][player_x].ground[resource]--;
			e->users[cs]->player.inv[resource]++;
			tmp_to_bc(&e->users[cs]->buf_write, "ok", 1);
		}
		else
			tmp_to_bc(&e->users[cs]->buf_write, "ko", 1);
	}
	gfx_send_npc(e, cs, gfx_pin);
	gfx_send_map(e, player_x, player_y, gfx_bct);
}

void			gfx_take_item(t_env *e, int cs)
{
	char		*item;
	int			resource;

	item = e->users[cs]->player.acts[e->users[cs]->player.cur_aread].cmd;
	resource = str_to_type(item);
	if (resource < 0)
		return ;
	gfx_send_act(e, cs, gfx_pgt, resource);
}
