/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_move_forward.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmansour <dmansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 18:24:39 by dmansour          #+#    #+#             */
/*   Updated: 2014/06/13 23:10:09 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>

t_ponf_cmd		g_tab[NBR_CMD];

void			move_forward(t_env *e, int cs)
{
	t_player		*p;

	p = &e->users[cs]->player;
	if (p->x == 0 && p->direc == WEST)
		p->x = e->opt.x;
	if (p->y == 0 && p->direc == NORTH)
		p->y = e->opt.y;
	if (p->direc == NORTH)
		p->y--;
	else if (p->direc == SOUTH)
		p->y = (p->y + 1) % e->opt.y;
	else if (p->direc == EAST)
		p->x = (p->x + 1) % e->opt.x;
	else if (p->direc == WEST)
		p->x--;
	tmp_to_bc(&e->users[cs]->buf_write, "OK", 1);
}
