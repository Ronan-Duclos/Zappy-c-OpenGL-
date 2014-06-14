/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_broadcast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/14 16:44:34 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/14 17:54:09 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <libft.h>

typedef struct			s_coord
{
	int			x;
	int			y;
}						t_coord;

int			get_dir_broadcast(t_env *env, t_coord *p1, t_coord *p2, int dir)
{
	int			dx;
	int			dy;
	int			res;

	dx = p1.x - p2.x;
	dy = p2.y - p2.y;
	dx = abs(dx) > env->opt.x / 2 ? dx = env->opt.x - dx : dx;
	dy = abs(dy) > env->opt.y / 2 ? dy = env->opt.y - dy : dy;
	res = 0;
	if (dx == dy && dx > 0)
		res = 8;
	else if (dx == dy && dx < 0)
		res = 4;
	else if (dx == -dy && dx > 0)
		res = 6;
	else if (dx == -dy && dx < 0)
		res = 2;
	else
	{
		if (abs(dx) > abs(dy) && dx > 0)
			res = 7;
		else if (abs(dx) > abs(dy) && dx < 0)
			res = 3;
		else if (abs(dx) < abs(dy) && dx > 0)
			res = 1;
		else if (abs(dx) < abs(dy) && dx < 0)
			res = 5;
	}
	res += dir * 2;
	return (res % 8);
}

int
