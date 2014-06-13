/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_turn_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmansour <dmansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 18:24:39 by dmansour          #+#    #+#             */
/*   Updated: 2014/06/12 18:34:42 by dmansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>

t_ponf_cmd		g_tab[NBR_CMD];

void			turn_right(t_env *e, int cs)
{
	if (e->users[cs]->player.direc == NORTH)
		e->users[cs]->player.direc = EAST;
	if (e->users[cs]->player.direc == EAST)
		e->users[cs]->player.direc = SOUTH;
	if (e->users[cs]->player.direc == SOUTH)
		e->users[cs]->player.direc = WEST;
	if (e->users[cs]->player.direc == WEST)
		e->users[cs]->player.direc = NORTH;
	tmp_to_bc(&e->users[cs]->buf_write, "OK", 1);
}
