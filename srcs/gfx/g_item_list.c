/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_item_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 18:42:59 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/17 01:22:00 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

void		list_item_init(t_env *env)
{
	glNewList(env->lists[_init_item_pos], GL_COMPILE);
	{
		glTranslatef(-1.0, -0.7, -1.0);
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glScalef(0.009, 0.009, 0.009);
	}
	glEndList();
	glNewList(env->lists[_init_plant_pos], GL_COMPILE);
	{
		glTranslatef(-1.0, 0.0, -1.0);
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glScalef(0.005, 0.005, 0.005);
	}
	glEndList();
}
