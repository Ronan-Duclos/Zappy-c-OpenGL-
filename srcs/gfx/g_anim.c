/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_anim.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 20:55:44 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/24 21:38:58 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
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

/*
**	Animates a model: He moves upwards, turning on itself while shrinking.
*/
void	anim_rock(t_anim *a)
{
	double	i;

	i = (double)a->frame;
	glTranslatef(0.0, 0.0, 0.5 * i);
	glScalef(1.0 - i / 500, 1.0 - i / 500, 1.0 - i / 500);
	glRotatef(2.0 * i, 0.0, 0.0, 1.0);
	a->frame++;
	if (a->frame >= a->maxframe)
		a->frame = 0;
}

/*
**	I used a sin(frame) on the y axis to move the player up and down.
*/
void	anim_mob(t_anim *a)
{
	float	i;

	i = sin(TORAD(a->frame)) / 10;
	glTranslatef(0.0, i, 0.0);
	a->frame++;
	if (a->frame >= a->maxframe)
		a->frame = 0;
}

void	anim_incant(t_anim *a)
{
	float	i;

	i = (float)a->frame / a->maxframe;
	glTranslatef(0.0, i - 1.0, 0.0);
	if (a->frame < a->maxframe)
		a->frame++;
}
