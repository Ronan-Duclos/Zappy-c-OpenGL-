/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_gfx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 16:54:11 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/15 20:55:34 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "serveur.h"
#include "libft.h"

/*
**	send map_size;
*/
void		gfx_msz(t_env *e, int cs)
{
	char	buf[BUF_SIZE];

	ft_bzero(buf, BUF_SIZE);
	sprintf(buf, "msz %d %d", e->opt.x, e->opt.y);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

/*
**	send time.
*/
void		gfx_sgt(t_env *e, int cs)
{
	char	buf[BUF_SIZE];

	ft_bzero(buf, BUF_SIZE);
	sprintf(buf, "sgt %d", e->opt.time);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

/*
**	send inventory of map[X][Y]
*/
void		gfx_bct(t_env *e, int cs, int x, int y)
{
	char	buf[BUF_SIZE];

	ft_bzero(buf, BUF_SIZE);
	sprintf(buf, "bct %d %d %d %d %d %d %d %d %d", x, y,
			e->map[x][y][_food],
			e->map[x][y][_linemate],
			e->map[x][y][_deraumere],
			e->map[x][y][_sibur],
			e->map[x][y][_mendiane],
			e->map[x][y][_phiras],
			e->map[x][y][_thystame]);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

/*
**	send map
*/
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
				gfx_bct(e, cs, e->users[cs]->gfx.i, e->users[cs]->gfx.j);
			x++;
			e->users[cs]->gfx.j++;
		}
	}
	if (x >= e->opt.x * e->opt.y)
	{
		e->users[cs]->ig = 1;
		e->users[cs]->gfx.i = 0;
	}
}

/*
**	Send team names
*/
void		gfx_tna(t_env *e, int cs)
{
	char	buf[BUF_SIZE];
	int		i;

	i = -1;
	while (e->opt.name[++i])
	{
		bzero(buf, BUF_SIZE);
		sprintf(buf, "tna %s", e->opt.name[i]);
		tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
	}
}

/*
**	send new connection: positions X Y, Orientation, level and team name
*/
void		gfx_pnw(t_env *e, int cs)
{
	char	buf[BUF_SIZE];
	int		i;

	i = -1;
	while (++i < e->srv.max_fd)
	{
		if (e->users[i]->type == FD_CLT && !e->users[i]->gfx.gfx)
		{
			bzero(buf, BUF_SIZE);
			sprintf(buf, "pnw #%d %d %d %d %d %s", i,
					e->users[i]->player.x,
					e->users[i]->player.y,
					e->users[i]->player.direc,
					e->users[i]->player.lvl,
					e->users[i]->player.team);
			tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
		}
	}
}

/*
**	send create Egg action: egg_nb player X Y
**	a faire quand les oeufs seront geres dans le serveur.
*/
void		gfx_enw(t_env *e, int cs)
{
	(void)e;
	(void)cs;
}

/*
**	send player #cs positon.
*/
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

void		gfx_end_init(t_env *e)
{
	t_glst	*tmp;

	printf("in end\n");
	tmp = e->srv.glst;
	while (tmp)
	{
		if (!e->users[tmp->cs]->ig)
			gfx_init(e, tmp->cs);
		tmp = tmp->next;
	}
}

void		gfx_init(t_env *e, int cs)
{
	t_glst		*new;

	e->users[cs]->gfx.gfx = 1;
	if (!e->users[cs]->gfx.state)
	{
		new = NULL;
		e->users[cs]->player.team = NULL;
		new = glst_new(cs);
		glst_add(&e->srv.glst, new);
		gfx_msz(e, cs);
		gfx_sgt(e, cs);
		e->users[cs]->gfx.state += 1;
	}
	if (e->users[cs]->gfx.state == 1 && !e->users[cs]->ig)
		gfx_mct(e, cs);
	else
	{
		gfx_tna(e, cs);
		gfx_pnw(e, cs);
		gfx_enw(e, cs);
	}
	glst_put(&e->srv.glst);
}
