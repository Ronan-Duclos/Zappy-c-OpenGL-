/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_incantation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/16 18:09:14 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/16 23:49:47 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>

static int		g_lvlup[7][8] = {
 	{0, 1, 0, 0, 0, 0, 0, 1},
	{0, 1, 1, 1, 0, 0, 0, 2},
	{0, 2, 0, 1, 0, 2, 0, 2},
	{0, 1, 1, 2, 0, 1, 0, 4},
	{0, 1, 2, 1, 3, 0, 0, 4},
	{0, 1, 2, 3, 0, 1, 0, 6},
	{0, 2, 2, 2, 2, 2, 1, 6}
};



void			incantation(t_env *e, int cs)
{
	int		x;
	int		y;
	int		lvl;
	int		good;
	int		i;

	x = e->users[cs]->player.x;
	y = e->users[cs]->player.y;
	lvl = e->users[cs]->player.lvl;
	good = 1;
	i = 0;
	while (++i < NB_STONE + 1)
		if (e->map[x][y].ground[i] < g_lvlup[lvl - 1][i])
			good = -1;
	if (good != -1)
		lvl = e->users[cs]->player.lvl++;
	char_to_bc(&e->users[cs]->buf_write, '0' + lvl);
	char_to_bc(&e->users[cs]->buf_write, '\n');
}
