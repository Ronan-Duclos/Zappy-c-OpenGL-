/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_display_squares.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 20:39:35 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/13 20:55:21 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

static void	display_square(int i)
{
	static GLfloat	vertices[] = {

	-1.0, 0.0, -1.0, 1.0, 0.0, -1.0, 1.0, 0.0, 1.0, -1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0
	};
	glNormalPointer(GL_FLOAT, 0, vertices + 12);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	(void)i;////TESUTO
	glBegin(GL_QUADS);
	{
//		glTexCoord2f((float)(i % 8) / 8.0, (4.0 - i / 8) / 4.0);
		glTexCoord2f(1.0, 1.0);
		glArrayElement(0);
//		glTexCoord2f((float)(i % 8 + 1) / 8.0, (4.0 - i / 8) / 4.0);
		glTexCoord2f(1.0, 0.0);
		glArrayElement(1);
//		glTexCoord2f((float)(i % 8 + 1) / 8.0, (3.0 - i / 8) / 4.0);
		glTexCoord2f(0.0, 0.0);
		glArrayElement(2);
//		glTexCoord2f((float)(i % 8) / 8.0, (3.0 - i / 8) / 4.0);
		glTexCoord2f(0.0, 1.0);
		glArrayElement(3);
	}
	glEnd();
}

void	display_all_squares(void)
{
	int	i;

	i = 0;
	glCallList(g_env->lists[_white]);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glBindTexture(GL_TEXTURE_2D, g_env->maptex);
	while (i < g_env->mapw * g_env->maph)
	{
		glPushMatrix();
		if (i == g_env->selectcase)
			glCallList(g_env->lists[_highlight]);
		glTranslatef(i % g_env->mapw * 2.0, 0.0, i / g_env->mapw * 2.0);
		display_square((int)g_env->sq[i].tile);
		if (i == g_env->selectcase)
			glCallList(g_env->lists[_white]);
		glPopMatrix();
		i++;
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}
