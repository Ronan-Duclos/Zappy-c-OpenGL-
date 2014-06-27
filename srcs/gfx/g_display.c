/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_display.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 19:50:07 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/27 07:15:02 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

void	display(void)
{
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRotatef(40.0, 1.0, 0.0, 0.0);
	glTranslatef(g_env->camtrans[0], g_env->camtrans[1], g_env->camtrans[2]);
	if (g_env->maph)
	{
		display_map();
//		display_footer();
	}
	glutSwapBuffers();
}
