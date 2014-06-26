/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_transpose.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 20:09:00 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/27 00:17:59 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

void	transpose(void)
{
	GLdouble	model[16];
	GLdouble	proj[16];
	GLint		view[4];
	GLdouble	posz0[3];
	GLdouble	posz1[3];

	glGetDoublev(GL_MODELVIEW_MATRIX, model);
	glGetDoublev(GL_PROJECTION_MATRIX, proj);
	glGetIntegerv(GL_VIEWPORT, view);
	gluUnProject(0, 0, 0, model, proj, view,
				posz0 + 0, posz0 + 1, posz0 + 2);
	gluUnProject(0, 0, 1, model, proj, view, posz1 + 0, posz1 + 1, posz1 + 2);
	map_intersection(g_env->realpos00, posz0, posz1);
	gluUnProject(0, g_env->winy, 0, model, proj, view,
				posz0 + 0, posz0 + 1, posz0 + 2);
	gluUnProject(0, g_env->winy, 1, model, proj, view,
				posz1 + 0, posz1 + 1, posz1 + 2);
	map_intersection(g_env->realpos0y, posz0, posz1);
	gluUnProject(g_env->winx, g_env->winy, 0, model, proj, view,
				posz0 + 0, posz0 + 1, posz0 + 2);
	gluUnProject(g_env->winx, g_env->winy, 1, model, proj, view,
				posz1 + 0, posz1 + 1, posz1 + 2);
	map_intersection(g_env->realposxy, posz0, posz1);
}
