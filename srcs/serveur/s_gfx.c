/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_gfx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 16:54:11 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/12 18:36:15 by caupetit         ###   ########.fr       */
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
	int		i;
	int		j;

	i = -1;
	while (++i < e->opt.x)
	{
		j = -1;
		while (++j < e->opt.y)
			gfx_bct(e, cs, i, j);
	}
}

/*
**	send team names
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
		if (e->users[i]->type == FD_CLT && !e->users[i]->gfx)
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
**	a faire quand les oeux seront geres dans le serveur.
*/
void		gfx_enw(t_env *e, int cs)
{
	(void)e;
	(void)cs;
}

/*
**	send player #cs positon.
*/
void		gfx_ppo(t_env *e, int cs)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	sprintf(buf, "ppo #%d %d %d %d", cs,
			e->users[cs]->player.x,
			e->users[cs]->player.y,
			e->users[cs]->player.direc);
	tmp_to_bc(&e->users[7]->buf_write, buf, 1);
}

void		gfx_init(t_env *e, int cs)
{
	t_glst	*new;

	new = NULL;
	e->users[cs]->ig = 1;
	e->users[cs]->gfx = 1;
	e->users[cs]->player.team = NULL;
	new = glst_new(cs);
	glst_add(&e->srv.glst, new);
	gfx_msz(e, cs);
	gfx_sgt(e, cs);
	gfx_mct(e, cs);
	gfx_tna(e, cs);
	gfx_pnw(e, cs);
	gfx_enw(e, cs);
	glst_put(&e->srv.glst);
}
