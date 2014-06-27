/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_gfx_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 17:32:56 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/27 07:32:35 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "libft.h"

void		gfx_bct(t_env *e, int cs, int y, int x)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	sprintf(buf, "bct %d %d %d %d %d %d %d %d %d", x, y,
			e->map[x][y].ground[_food],
			e->map[x][y].ground[_linemate],
			e->map[x][y].ground[_deraumere],
			e->map[x][y].ground[_sibur],
			e->map[x][y].ground[_mendiane],
			e->map[x][y].ground[_phiras],
			e->map[x][y].ground[_thystame]);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

void		gfx_mct(t_env *e, int cs)
{
	int			x;

	x = 0;
	while (x < 20 && e->users[cs]->gfx.i < e->opt.x)
	{
		if (e->users[cs]->gfx.j >= e->opt.y)
			e->users[cs]->gfx.i++;
		if (e->users[cs]->gfx.j >= e->opt.y)
			e->users[cs]->gfx.j = 0;
		while (x < 20 && e->users[cs]->gfx.j < e->opt.y)
		{
			if (e->users[cs]->gfx.i < e->opt.x)
				gfx_bct(e, cs, e->users[cs]->gfx.j, e->users[cs]->gfx.i);
			x++;
			e->users[cs]->gfx.j++;
			e->users[cs]->gfx.x++;
		}
	}
	if (e->users[cs]->gfx.x >= e->opt.x * e->opt.y)
	{
		e->users[cs]->gfx.state += 1;
		e->users[cs]->gfx.i = 0;
	}
}

void		gfx_pnw(t_env *e, int cs, int i)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	sprintf(buf, "pnw #%d %d %d %d %d %s", i,
			e->users[i]->player.x,
			e->users[i]->player.y,
			e->users[i]->player.direc,
			e->users[i]->player.lvl,
			e->users[i]->player.team);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

void		gfx_ppo(t_env *e, int cs, int clt)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	sprintf(buf, "ppo #%d %d %d %d", clt,
			e->users[clt]->player.x,
			e->users[clt]->player.y,
			e->users[clt]->player.direc);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}
