/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_gfx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 16:54:11 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/22 16:46:05 by caupetit         ###   ########.fr       */
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
**	Send player #cs positon to clt gfx socket.
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

/*
**	Send player's clt inventory
*/
void		gfx_pin(t_env *e, int cs, int clt)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	sprintf(buf, "pin #%d %d %d %d %d %d %d %d %d %d", clt,
			e->users[clt]->player.x,
			e->users[clt]->player.y,
			e->users[clt]->player.inv[_food],
			e->users[clt]->player.inv[_linemate],
			e->users[clt]->player.inv[_deraumere],
			e->users[clt]->player.inv[_sibur],
			e->users[clt]->player.inv[_mendiane],
			e->users[clt]->player.inv[_phiras],
			e->users[clt]->player.inv[_thystame]);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

/*
**	Send player's level
*/
void		gfx_plv(t_env *e, int cs, int clt)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	sprintf(buf, "plv #%d %d", clt, e->users[clt]->player.lvl);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

/*
**	Send signal wen player die
*/
void		gfx_pdi(t_env *e, int cs, int clt)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	sprintf(buf, "pdi #%d", clt);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

/*
**	Send signal wen player fork
*/
void		gfx_pfk(t_env *e, int cs, int clt)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	sprintf(buf, "pfk #%d", clt);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

/*
**	Send signal for incantation
*/
void		gfx_pic(t_env *e, int cs, int clt)
{
	t_user	*tmp;
	char	buf[BUF_SIZE];
	int		i;
	int		lvl;

	bzero(buf, BUF_SIZE);
	i = 0;
	tmp = e->map[e->users[clt]->player.x][e->users[clt]->player.y].player;
	lvl = tmp->player.lvl;
	i += sprintf(buf, "pic %d %d %d", e->users[clt]->player.x, 
				 e->users[clt]->player.y,
				 tmp->player.lvl);
	while (tmp)
	{
		if (tmp->player.lvl == lvl)
			i += sprintf(&buf[i], " #%d", tmp->sock);
		tmp = tmp->next;
	}
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

/*
**	Send signal for end of incantation
*/
void		gfx_pie(t_env *e, int cs, int clt, int succes)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	if (succes != 1)
		succes = 0;
	sprintf(buf, "pie %d %d %d", e->users[clt]->player.x,
			e->users[clt]->player.y, succes);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

/*
**	Send signal wen player take ressource
*/
void		gfx_pgt(t_env *e, int cs, int clt, int itm)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	sprintf(buf, "pgt #%d %d", clt, itm);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

/*
**	Send signal wen player drop ressource
*/
void		gfx_pdr(t_env *e, int cs, int clt, int itm)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	sprintf(buf, "pdr #%d %d", clt, itm);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

/*
**	Send all gfx clients the function as
**	void (*fu)(t_env *e, int gfx_cs, int clt)
**	cs is id/socket of client you want to send infos.
*/
void		gfx_send_npc(t_env *e, int cs, void (*fu)())
{
	t_glst	*tmp;

	tmp = e->srv.glst;
	while (tmp)
	{
		fu(e, tmp->cs, cs);
		tmp = tmp->next;
	}
}

/*
**	Send all gfx clients the function as
**	void (*fu)(t_env *e, int gfx_cs, int clt, int itm)
**	cs is id/socket of client you want to send infos.
**	itm is the item taked or droped (see e_map enum)
*/
void		gfx_send_act(t_env *e, int cs, void (*fu)(), int itm)
{
	t_glst	*tmp;

	tmp = e->srv.glst;
	while (tmp)
	{
		fu(e, tmp->cs, cs, itm);
		tmp = tmp->next;
	}
}

/*
**	Send all gfx clients the function as
**	void (*fu)(t_env *e, int cs. int x, int y)
**	x y location of map case you want to send info.
*/
void		gfx_send_map(t_env *e, int x, int y, void (*fu)())
{
	t_glst	*tmp;

	tmp = e->srv.glst;
	while (tmp)
	{
		fu(e, tmp->cs, x, y);
		tmp = tmp->next;
	}
}
