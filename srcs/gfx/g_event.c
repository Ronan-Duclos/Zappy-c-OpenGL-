/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_event.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 19:56:36 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/13 20:17:53 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

void	reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	g_env->winx = w;
	g_env->winy = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void	idle(void)
{
	if (!time_frame())
	{
		if (g_env->keys & FLAG_RIGHT)
			g_env->camtrans[0] += -0.2;
		if (g_env->keys & FLAG_LEFT)
			g_env->camtrans[0] += 0.2;
		if (g_env->keys & FLAG_UP)
			g_env->camtrans[2] += 0.2;
		if (g_env->keys & FLAG_DOWN)
			g_env->camtrans[2] += -0.2;
		if (g_env->keys)
			transpose();
		glutPostRedisplay();
	}
}
