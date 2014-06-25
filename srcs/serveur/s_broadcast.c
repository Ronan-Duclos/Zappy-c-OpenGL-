/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_broadcast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/14 16:44:34 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/25 23:50:43 by rbernand         ###   ########.fr       */
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
	res = dx == dy && dx > 0 ? 6 : res;
	res = dx == dy && dx < 0 ? 2 : res;
	res = dx == -dy && dx > 0 ? 8 : res;
	res = dx == -dy && dx < 0 ? 4 : res;
	if (dx == dy || dx == -dy)
		return (res > 8 ? res - 8 : res);
	res = abs(dx) > abs(dy) && dx > 0 ? 3 : res;
	res = abs(dx) > abs(dy) && dx < 0 ? 7 : res;
	res = abs(dx) < abs(dy) && dy > 0 ? 1 : res;
	res = abs(dx) < abs(dy) && dy < 0 ? 5 : res;
	res += p2->direc * 2;
	printf("in bc : res [%d] dx [%d] dy[%d]\n", res, dx, dy);
	return (res > 8 ? res - 8 : res);
}

static int			broadcast_one(t_env *env, char *msg, int ori, int cs)
{
	char		buf[4096];

	bzero(buf, 4096);
	sprintf(buf, "message %d, %s", get_dir_broadcast(env,
				&env->users[ori]->player, &env->users[cs]->player), msg);
	tmp_to_bc(&env->users[cs]->buf_write, buf, 1);
	return (0);
}

void				broadcast(t_env *env, int cs)
{
	int			i;
	int			max_fd;
	char		*msg;

	msg = env->users[cs]->player.acts[env->users[cs]->player.cur_aread].cmd;
	max_fd = env->srv.max_fd;
	gfx_send_pcb(env, cs, msg, gfx_pcb);
	i = -1;
	while (++i < max_fd)
		if (env->users[i]->type == FD_CLT && i != cs && !env->users[i]->gfx.gfx)
			broadcast_one(env, msg, cs, i);
	tmp_to_bc(&env->users[cs]->buf_write, "ok", 1);
}
