/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 19:53:45 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/27 00:14:57 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

void	speckey(int key, int xmouse, int ymouse)
{
	int			i;
	static int	tab[] = {

	GLUT_KEY_LEFT, FLAG_LEFT,
	GLUT_KEY_DOWN, FLAG_DOWN,
	GLUT_KEY_RIGHT, FLAG_RIGHT,
	GLUT_KEY_UP, FLAG_UP,
	0, 0};
	i = 0;
	(void)xmouse;
	(void)ymouse;
	while (tab[i] != 0 && tab[i] != key)
		i += 2;
	if (tab[i])
		g_env->keys |= tab[i + 1];
}

void	speckeyup(int key, int xmouse, int ymouse)
{
	int			i;
	static int	tab[] = {

	GLUT_KEY_LEFT, FLAG_LEFT,
	GLUT_KEY_DOWN, FLAG_DOWN,
	GLUT_KEY_RIGHT, FLAG_RIGHT,
	GLUT_KEY_UP, FLAG_UP,
	0, 0};
	i = 0;
	(void)xmouse;
	(void)ymouse;
	while (tab[i] != 0 && tab[i] != key)
		i += 2;
	if (tab[i])
		g_env->keys &= ~tab[i + 1];
}

void	motion(int x, int y)
{
	GLdouble	model[16];
	GLdouble	proj[16];
	GLint		view[4];
	GLdouble	posz0[3];
	GLdouble	posz1[3];
	GLdouble	pos[3];

	glGetDoublev(GL_MODELVIEW_MATRIX, model);
	glGetDoublev(GL_PROJECTION_MATRIX, proj);
	glGetIntegerv(GL_VIEWPORT, view);
	gluUnProject(x, g_env->winy - y, 0, model, proj, view,
				posz0 + 0, posz0 + 1, posz0 + 2);
	gluUnProject(x, g_env->winy - y, 1, model, proj, view,
				posz1 + 0, posz1 + 1, posz1 + 2);
	map_intersection(pos, posz0, posz1);
	x = (int)((pos[0] + 1) / 2);
	y = (int)((pos[2] + 1) / 2);
	if (x > g_env->mapw - 1 || y > g_env->maph - 1 || x < 0 || y < 0)
		g_env->selectcase = -1;
	else
		g_env->selectcase = x + y * g_env->mapw;
}
