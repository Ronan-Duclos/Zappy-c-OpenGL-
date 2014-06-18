/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_turn_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmansour <dmansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 18:24:39 by dmansour          #+#    #+#             */
/*   Updated: 2014/06/18 22:34:25 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>

t_ponf_cmd		g_tab[NBR_CMD];

void			turn_left(t_env *e, int cs)
{
	if (e->users[cs]->player.direc == NORTH)
		e->users[cs]->player.direc = WEST;
	else
		e->users[cs]->player.direc--;
	tmp_to_bc(&e->users[cs]->buf_write, "OK", 1);
}

void			gfx_turn_left(t_env *e, int cs)
{
	if (e->users[cs]->player.direc == NORTH)
		e->users[cs]->player.direc = WEST;
	else
		e->users[cs]->player.direc--;
	gfx_send_npc(e, cs, gfx_ppo);
	e->users[cs]->player.direc = (e->users[cs]->player.direc + 1) % 4;
}
