/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_vec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 20:28:45 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/27 00:17:13 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "gfx_gl.h"

void	normalize(GLdouble vec[3])
{
	double	mag;

	mag = MAG(vec);
	vec[0] /= mag;
	vec[1] /= mag;
	vec[2] /= mag;
}

void	getdir(GLdouble o[3], GLdouble dir[3])
{
	dir[0] -= o[0];
	dir[1] -= o[1];
	dir[2] -= o[2];
}

void	getdirf(GLfloat o[3], GLfloat dir[3])
{
	dir[0] -= o[0];
	dir[1] -= o[1];
	dir[2] -= o[2];
}

void	map_intersection(GLdouble *inter, GLdouble *a, GLdouble *b)
{
	double	t;

	getdir(a, b);
	normalize(b);
	t = (1.0 * -a[1]) / (1.0 * b[1]);
	inter[0] = a[0] + b[0] * t;
	inter[1] = a[1] + b[1] * t;
	inter[2] = a[2] + b[2] * t;
}

void	set_vecf(GLfloat vec[3], GLfloat x, GLfloat y, GLfloat z)
{
	vec[_x] = x;
	vec[_y] = y;
	vec[_z] = z;
}
