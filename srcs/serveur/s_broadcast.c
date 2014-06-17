/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_broadcast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/14 16:44:34 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/17 07:12:42 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <libft.h>

static int			get_dir_broadcast(t_env *env, t_player *p1, t_player *p2)
{
	int			dx;
	int			dy;
	int			res;

	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	if (dx == 0 && dy == 0)
		return (0);
	dx = abs(dx) > env->opt.x / 2 ? -(env->opt.x - dx) : dx;
	dy = abs(dy) > env->opt.y / 2 ? -(env->opt.y - dy) : dy;
	res = 0;
	if (dx == dy && dx > 0)
		res = 2;
	else if (dx == dy && dx < 0)
		res = 6;
	else if (dx == -dy && dx > 0)
		res = 4;
	else if (dx == -dy && dx < 0)
		res = 8;
	else if (abs(dx) > abs(dy) && dx > 0)
		res = 3;
	else if (abs(dx) > abs(dy) && dx < 0)
		res = 7;
	else if (abs(dx) < abs(dy) && dy > 0)
		res = 1;
	else if (abs(dx) < abs(dy) && dy < 0)
		res = 5;
	res += p2->direc * 2;
	if (res > 8)
		return (res - 8);
	return (res);
}

static int			broadcast_one(t_env *env, char *msg, int ori, int cs)
{
	char		buf[4096];

	bzero(buf, 4096);
	sprintf(buf, "message %d,%s", get_dir_broadcast(env, &env->users[ori]->player,
				&env->users[cs]->player), msg);
	tmp_to_bc(&env->users[cs]->buf_write, buf, 1);
	return (0);
}

void		broadcast(t_env *env, int cs)
{
	int			i;
	int			max_fd;
	char		*msg;

	msg = env->users[cs]->player.acts[env->users[cs]->player.cur_aread].cmd;
	max_fd = env->srv.max_fd;
	i = -1;
	while (++i < max_fd)
		if (env->users[i]->type == FD_CLT && i != cs)
			broadcast_one(env, msg, cs, i);
}
