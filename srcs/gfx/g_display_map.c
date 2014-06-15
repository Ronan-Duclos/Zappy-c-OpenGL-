/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_display_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 20:37:42 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/13 22:56:55 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

void	display_map(void)
{
	int		i;

	display_all_squares();
	display_all_grid();
	i = 0;
	glDisable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbo_vrtx);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbo_nrms);
	glNormalPointer(GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	while (i < g_env->mapw * g_env->maph)
	{
		if (g_env->realpos0y[0] > i % g_env->mapw * 2.0 + 1.0
			|| g_env->realposxy[0] < i % g_env->mapw * 2.0 - 1.0
			|| g_env->realposxy[2] > i / g_env->mapw * 2.0 + 1.0
			|| g_env->realpos00[2] < i / g_env->mapw * 2.0 - 1.0)
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
	glDisableClientState(GL_NORMAL_ARRAY | GL_VERTEX_ARRAY);
}
