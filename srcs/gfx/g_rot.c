/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_rot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/21 17:40:51 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/21 19:14:23 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

t_rot		*new_rot(int frames, GLfloat vec[3], GLfloat angle, GLfloat rot)
{
	t_rot	*new;

	new = (t_rot *)XV(NULL, malloc(sizeof(t_rot)), "malloc");
	new->frames = frames;
	new->vec[0] = vec[0];
	new->vec[1] = vec[1];
	new->vec[2] = vec[2];
	new->angle = angle;
	new->rot = rot;
	return (new);
}

void		anim_rot(t_rot *r)
{
	glRotatef(r->angle, r->vec[_x], r->vec[_y], r->vec[_z]);
	if (!r->frames)
		return ;
	r->angle += r->rot;
	r->frames--;
}

void		rot_init(t_rot *rot, enum e_dir direc)
{
	int			fram;
	int			angle;

	fram = FPS * T_RIGHT / g_env->time;
	rot->frames = fram;
	angle = direc * 90;
	rot->rot = (angle - rot->angle) / fram;
	if (rot->angle >= 360.0)
		rot->angle -= 360.0;
	if (rot->angle <= 0.0)
		rot->angle += 360.0;
}
