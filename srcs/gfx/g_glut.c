/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_glut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 19:15:31 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/13 19:16:08 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

void	init_glut(int ac, char **av)
{
	glutInit(&ac, av);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(30, 30);
	glutInitWindowSize(SCR_WID, SCR_HGH);
	glutCreateWindow("*HOSHI* TESUTO DA YO NE~ *HOSHI*");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(speckey);
	glutSpecialUpFunc(speckeyup);
	glutPassiveMotionFunc(motion);
	glutIdleFunc(idle);
}
