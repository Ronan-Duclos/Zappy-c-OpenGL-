/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_rot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/21 17:40:51 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/22 17:17:44 by tmielcza         ###   ########.fr       */
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
	glRotatef(-r->angle, r->vec[_x], r->vec[_y], r->vec[_z]);
	if (!r->frames)
		return ;
	r->angle += r->rot;
	r->frames--;
}

void		rot_init(t_rot *rot, enum e_dir direc)
{
	int			fram;
	float		angle;

	fram = FPS * T_RIGHT / g_env->time;
	rot->frames = fram;
	angle = 90.0 * direc - rot->angle;
	printf("angle = %f\n", angle);
	if (angle > 180.0)
		angle = angle - 360;
	if (angle < -180.0)
		angle = 360.0 + angle;
	rot->rot = angle / fram;
	printf("angle = %f, rot = %f, calc = %f\n", rot->angle, rot->rot, angle);
	if (rot->angle > 360.0)
		rot->angle -= 360.0;
	if (rot->angle <= 0.0)
		rot->angle += 360.0;
}
