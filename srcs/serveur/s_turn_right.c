/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_turn_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmansour <dmansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 18:24:39 by dmansour          #+#    #+#             */
/*   Updated: 2014/06/18 22:35:23 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>

t_ponf_cmd		g_tab[NBR_CMD];

void			turn_right(t_env *e, int cs)
{
	e->users[cs]->player.direc = (e->users[cs]->player.direc + 1) % 4;
	tmp_to_bc(&e->users[cs]->buf_write, "OK", 1);
}

void			gfx_turn_right(t_env *e, int cs)
{
	e->users[cs]->player.direc = (e->users[cs]->player.direc + 1) % 4;
	gfx_send_npc(e, cs, gfx_ppo);
	if (e->users[cs]->player.direc == NORTH)
		e->users[cs]->player.direc = WEST;
	else
		e->users[cs]->player.direc--;
}
