/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 01:25:35 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/22 20:38:31 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GLUT/glut.h>
#include "gfx_gl.h"

void	list_pink_init(void)
{
	static	GLfloat mat_specular[] = JADE_SPEC;
	static	GLfloat mat_diffuse[] = JADE_DIFF;
	static	GLfloat mat_ambient[] = JADE_AMBI;

	glNewList(g_env->lists[_pink], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glEndList();
}

void	list_cyan_init(void)
{
	static	GLfloat mat_specular[] = BLACK_SPEC;
	static	GLfloat mat_diffuse[] = BLACK_DIFF;
	static	GLfloat mat_ambient[] = BLACK_AMBI;

	glNewList(g_env->lists[_cyan], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glEndList();
}

void	list_highlight_init(void)
{
	static	GLfloat mat_specular[] = { 0.4, 0.4, 0.4, 1.0 };
	static	GLfloat mat_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
	static	GLfloat mat_ambient[] = { 0.4, 0.4, 0.4, 1.0 };

	glNewList(g_env->lists[_highlight], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glEndList();
}
