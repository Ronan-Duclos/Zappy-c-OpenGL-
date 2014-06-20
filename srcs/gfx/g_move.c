/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_move.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/18 19:33:04 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/20 02:49:15 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

t_move		*new_move(int frames, GLfloat pos[3], GLfloat dir[3])
{
	t_move	*new;

	new = (t_move *)XV(NULL, malloc(sizeof(t_move)), "malloc");
	new->frames = frames;
	new->pos[0] = pos[0];
	new->pos[1] = pos[1];
	new->pos[2] = pos[2];
	new->dir[0] = dir[0];
	new->dir[1] = dir[1];
	new->dir[2] = dir[2];
	return (new);
}

void		anim_move(t_move *m)
{
	glTranslatef(m->pos[_x], m->pos[_y], m->pos[_z]);
	if (!m->frames)
		return ;
	m->pos[0] += m->dir[0];
	m->pos[1] += m->dir[1];
	m->pos[2] += m->dir[2];
	m->frames--;
}

void		move_init(t_move *move, int x, int y)
{
	GLfloat		dir[3];
	int			fram;

	fram = 60;
	move->frames = fram;
	set_vecf(dir, (float)x * 2, 0.0, (float)y * 2);
	printf("\nBLUT\nx %f, y %f, z %f\n", move->pos[_x], move->pos[_y], move->pos[_z]);
	printf("X = %d Y = %d\n", x, y);
	printf("\nx %f, y %f, z %f\n", dir[_x], dir[_y], dir[_z]);
	getdirf(move->pos, dir);
	set_vecf(dir, dir[_x] / fram, dir[_y] / fram, dir[_z] / fram);
	printf("\nx %f, y %f, z %f\n", dir[_x], dir[_y], dir[_z]);
	move->dir[_x] = dir[_x];
	move->dir[_y] = dir[_y];
	move->dir[_z] = dir[_z];
}
