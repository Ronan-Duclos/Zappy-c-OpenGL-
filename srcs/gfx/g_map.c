/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 23:38:37 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/17 15:01:53 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>
#include <stdlib.h>
#include "gfx.h"

static void	rand_itm_pos(t_square *sq)
{
	int		i;
	int		one;
	int		two;
	int		tmp;

	i = -1;
	while (++i < 200)
	{
		one = rand_int(0, 255);
		two = rand_int(0, 255);
		tmp = sq->grid[one];
		sq->grid[one] = sq->grid[two];
		sq->grid[two] = tmp;
	}
}

void		map_init(void)
{
	int		size;
	int		i;
	int		j;

	size = g_env->mapw * g_env->maph;
	g_env->sq = (t_square *)XV(NULL, malloc(sizeof(t_square) * (size + 1)), "map");
	bzero(g_env->sq, sizeof(t_square) * (size + 1));
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < CASE_MAX_ITEMS - 1)
			g_env->sq[i].grid[j] = j;
		rand_itm_pos(&g_env->sq[i]);
		g_env->sq[i].tile = rand() % 8;
	}
}
