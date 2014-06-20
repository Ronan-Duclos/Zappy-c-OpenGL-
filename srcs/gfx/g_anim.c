/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_anim.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 20:55:44 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/20 23:54:34 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "gfx_gl.h"

t_anim	*new_anim(int frame, int time, void (*fct)(t_anim *))
{
	t_anim	*new;

	new = (t_anim *)XV(NULL, malloc(sizeof(t_anim)), "malloc");
	new->maxframe = time;
	new->frame = frame;
	new->dead = 0;
	new->fct = fct;
	return (new);
}

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

void	anim_mob(t_anim *a)
{
	void(a);
}
