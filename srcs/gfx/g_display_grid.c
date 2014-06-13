/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_display_grid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 20:42:05 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/13 20:52:19 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

static void	display_grid()
{
	static GLfloat	vertices[] = {

	-1.0, 0.05, -1.0, 1.0, 0.05, -1.0, 1.0, 0.05, 1.0, -1.0, 0.05, 1.0
	};
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glBegin(GL_LINE_LOOP);
	{
		glColor3f(1.0, 1.0, 0.0);
		glArrayElement(0);
		glArrayElement(1);
		glArrayElement(2);
		glArrayElement(3);
	}
	glEnd();
}

void		display_all_grid(void)
{
	int		i;

	i = 0;
	glLineWidth(2.0);
	glDisable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_LIGHTING);
	while (i < g_env->mapw * g_env->maph)
	{
		glPushMatrix();
		glTranslatef(i % g_env->mapw * 2.0, 0.0, i / g_env->mapw * 2.0);
		display_grid();
		glPopMatrix();
		i++;
	}
	glEnable(GL_LIGHTING);
	glDisableClientState(GL_VERTEX_ARRAY);
}
