/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_light.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 19:24:58 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/13 22:56:58 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

void	light_init(void)
{
	static GLfloat	light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	static GLfloat	light_position[] = { 50.0, 150.0, 50.0, 0.0 };

	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}
