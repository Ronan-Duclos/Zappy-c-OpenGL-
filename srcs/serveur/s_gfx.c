/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_gfx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 16:54:11 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/16 15:24:59 by caupetit         ###   ########.fr       */
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
			e->map[x][y].ground[_food],
			e->map[x][y].ground[_linemate],
			e->map[x][y].ground[_deraumere],
			e->map[x][y].ground[_sibur],
			e->map[x][y].ground[_mendiane],
			e->map[x][y].ground[_phiras],
			e->map[x][y].ground[_thystame]);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

/*
**	Send bct for all map and breaks every 20 cases.
**	Circular buffer corrupted stack before that !!!
**	How uncredible powerfull buffer !
**	For each gfx fd, restart at the point it ended.
**	Recal made by gfx_end_init().
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
			e->users[cs]->gfx.x++;
		}
	}
	if (e->users[cs]->gfx.x >= e->opt.x * e->opt.y)
	{
		e->users[cs]->gfx.state += 1;
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
**	send player's i new connection:
**	positions X Y, Orientation, level and team name
*/
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
**	send player #cs positon to clt gfx socket.
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
