/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_display_squares.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 20:39:35 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/24 03:46:27 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

static void	init_tex_coord(GLfloat **texcoord)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	*texcoord = (GLfloat *)XV(NULL, malloc(sizeof(GLfloat) * 2 * 4 * 8), "malloc");
	while (i < 64)
	{
		j = (i / 8) + 4 + ((i / 8) / 2 * 6);
		(*texcoord)[i] = (float)(j % 8) / 8.0;
		(*texcoord)[i + 1] = (4.0 - j / 8) / 4.0;
		(*texcoord)[i + 2] = (float)(j % 8 + 1) / 8.0;
		(*texcoord)[i + 3] = (4.0 - j / 8) / 4.0;
		(*texcoord)[i + 4] = (float)(j % 8 + 1) / 8.0;
		(*texcoord)[i + 5] = (3.0 - j / 8) / 4.0;
		(*texcoord)[i + 6] = (float)(j % 8) / 8.0;
		(*texcoord)[i + 7] = (3.0 - j / 8) / 4.0;
		i += 8;
	}
}

static void	display_square(int i)
{
	static GLfloat	*texcoord = NULL;
	static GLfloat	vertices[] = {

	-1.0, 0.0, -1.0, 1.0, 0.0, -1.0, 1.0, 0.0, 1.0, -1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0
	};

	if (!texcoord)
		init_tex_coord(&texcoord);
	glNormalPointer(GL_FLOAT, 0, vertices + 12);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoord + i * 8);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glBegin(GL_QUADS);
	{
		glArrayElement(0);
		glArrayElement(1);
		glArrayElement(2);
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
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D, g_env->maptex);
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
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
