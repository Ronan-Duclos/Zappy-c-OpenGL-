/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_display_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 20:37:42 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/26 22:49:46 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

void	display_map(void)
{
	int		i;

	display_all_squares();
	display_all_grid();
	display_all_mobs();
	i = 0;
	while (i < g_env->mapw * g_env->maph)
	{
		if (g_env->realpos0y[0] > i % g_env->mapw * 2.0 + 3.0
			|| g_env->realposxy[0] < i % g_env->mapw * 2.0 - 3.0
			|| g_env->realposxy[2] > i / g_env->mapw * 2.0 + 3.0
			|| g_env->realpos00[2] < i / g_env->mapw * 2.0 - 3.0)
		{
			i++;
			continue ;
		}
		glPushMatrix();
		glTranslatef(i % g_env->mapw * 2.0, 0.0, i / g_env->mapw * 2.0);
		display_items(i);
		glPopMatrix();
		i++;
	}
}
