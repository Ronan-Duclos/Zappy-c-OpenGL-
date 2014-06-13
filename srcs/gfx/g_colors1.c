/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 01:19:58 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/11 01:26:58 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GLUT/glut.h>
#include "testopengl.h"

void	ft_color_white(void)
{
	static	GLfloat mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
	static	GLfloat mat_diffuse[] = { 0.9, 0.9, 0.9, 1.0 };
	static	GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };

	glNewList(g_env->colors[_white], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glEndList();
}

void	ft_color_red(void)
{
	static	GLfloat mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
	static	GLfloat mat_diffuse[] = { 0.9, 0.0, 0.0, 1.0 };
	static	GLfloat mat_ambient[] = { 0.5, 0.2, 0.2, 1.0 };

	glNewList(g_env->colors[_red], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glEndList();
}

void	ft_color_blue(void)
{
	static	GLfloat mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
	static	GLfloat mat_diffuse[] = { 0.0, 0.0, 0.9, 1.0 };
	static	GLfloat mat_ambient[] = { 0.2, 0.2, 0.5, 1.0 };

	glNewList(g_env->colors[_blue], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glEndList();
}

void	ft_color_green(void)
{
	static	GLfloat mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
	static	GLfloat mat_diffuse[] = { 0.0, 0.9, 0.0, 1.0 };
	static	GLfloat mat_ambient[] = { 0.2, 0.5, 0.2, 1.0 };

	glNewList(g_env->colors[_green], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glEndList();
}

void	ft_color_yellow(void)
{
	static	GLfloat mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
	static	GLfloat mat_diffuse[] = { 0.9, 0.9, 0.0, 1.0 };
	static	GLfloat mat_ambient[] = { 0.5, 0.5, 0.2, 1.0 };

	glNewList(g_env->colors[_yellow], GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glEndList();
}
