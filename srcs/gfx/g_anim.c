/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_anim.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 20:55:44 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/13 20:59:40 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

void	anim_rock(t_anim *a)
{
	double	i;

	if (a->dead)
	{
		a->frame = 0;
		a->dead = 0;
		return ;
	}
	i = (double)a->frame;
	glTranslatef(0.0, 0.0, 0.5 * i);
	glScalef(1.0 - i / 500, 1.0 - i / 500, 1.0 - i / 500);
	glRotatef(2.0 * i, 0.0, 0.0, 1.0);
	a->frame++;
	if (a->frame >= a->maxframe)
		a->dead = 1;
}
