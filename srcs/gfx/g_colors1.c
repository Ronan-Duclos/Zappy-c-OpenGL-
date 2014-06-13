/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 01:19:58 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/13 19:09:45 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GLUT/glut.h>
#include "gfx_gl.h"

void	list_white_init(void)
{
	static	GLfloat mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
	static	GLfloat mat_diffuse[] = { 0.9, 0.9, 0.9, 1.0 };
	static	GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };

	glNewList(g_env->lists[_white], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glEndList();
}

void	list_red_init(void)
{
	static	GLfloat mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
	static	GLfloat mat_diffuse[] = { 0.9, 0.0, 0.0, 1.0 };
	static	GLfloat mat_ambient[] = { 0.5, 0.2, 0.2, 1.0 };

	glNewList(g_env->lists[_red], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glEndList();
}

void	list_blue_init(void)
{
	static	GLfloat mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
	static	GLfloat mat_diffuse[] = { 0.0, 0.0, 0.9, 1.0 };
	static	GLfloat mat_ambient[] = { 0.2, 0.2, 0.5, 1.0 };

	glNewList(g_env->lists[_blue], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glEndList();
}

void	list_green_init(void)
{
	static	GLfloat mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
	static	GLfloat mat_diffuse[] = { 0.0, 0.9, 0.0, 1.0 };
	static	GLfloat mat_ambient[] = { 0.2, 0.5, 0.2, 1.0 };

	glNewList(g_env->lists[_green], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glEndList();
}

void	list_yellow_init(void)
{
	static	GLfloat mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
	static	GLfloat mat_diffuse[] = { 0.9, 0.9, 0.0, 1.0 };
	static	GLfloat mat_ambient[] = { 0.5, 0.5, 0.2, 1.0 };

	glNewList(g_env->lists[_yellow], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glEndList();
}
