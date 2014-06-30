/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_incantation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/16 18:09:14 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/27 11:22:20 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>
#include <libft.h>
#include <global.h>

void			make_lvlup(t_env *e, t_user *tmp)
{
	tmp->player.lvl = tmp->player.lvl + 1;
	gfx_send_npc(e, tmp->sock, gfx_plv);
	tmp_to_bc(&e->users[tmp->sock]->buf_write, "niveau actuel : ", 0);
	char_to_bc(&e->users[tmp->sock]->buf_write, '0' + tmp->player.lvl);
	tmp_to_bc(&e->users[tmp->sock]->buf_write, "", 1);
	tmp->player.lvlup = 0;
	tmp->player.lvlup_good = 0;
}

void			dont_lvlup(t_env *e, t_user *tmp)
{
	gfx_send_npc(e, tmp->sock, gfx_plv);
	tmp_to_bc(&e->users[tmp->sock]->buf_write, "niveau actuel : ", 0);
	char_to_bc(&e->users[tmp->sock]->buf_write, '0' + tmp->player.lvl);
	tmp_to_bc(&e->users[tmp->sock]->buf_write, "", 1);
	tmp->player.lvlup = 0;
	tmp->player.lvlup_good = 0;
}

void			end_incant(t_env *e, int cs, int good)
{
	int		x;
	int		y;
	int		i;
	t_user	*tmp;

	i = 0;
	x = e->users[cs]->player.x;
	y = e->users[cs]->player.y;
	tmp = e->map[y][x].player;
	while (tmp != NULL)
	{
		if (tmp->player.lvlup_good == 1 && (i = 1) == 1)
			make_lvlup(e, tmp);
		else if (tmp->player.lvlup == 1)
			dont_lvlup(e, tmp);
		tmp = tmp->next;
	}
	if (good == 1)
	{
		gfx_send_act(e, cs, gfx_pie, good);
		disperse_stone(e, cs, good);
		gfx_send_map(e, x, y, gfx_bct);
	}
}

int				last_inc(t_env *e, int cs)
{
	int			x;
	int			y;
	t_user		*tmp;
	int			sock;

	x = e->users[cs]->player.x;
	y = e->users[cs]->player.y;
	tmp = e->map[y][x].player;
	sock = tmp->sock;
	while (tmp->next != NULL)
	{
		if (tmp->sock > sock)
			sock = tmp->sock;
		tmp = tmp->next;
	}
	if (tmp->sock > sock)
		sock = tmp->sock;
	if (sock == cs)
		return (1);
	return (0);
}

int				check_lvl_users(t_env *e, int cs, int x, int y)
{
	t_user	*tmp;
	int		good;

	good = 0;
	tmp = e->map[y][x].player;
	while (tmp != NULL)
	{
		if (tmp->player.lvl == e->users[cs]->player.lvl)
			good++;
		tmp = tmp->next;
	}
	if (good >= g_lvlup[e->users[cs]->player.lvl - 1][_player])
		return (1);
	return (-1);
}

void			incantation(t_env *e, int cs)
{
	int		x;
	int		y;
	int		lvl;
	int		good;
	int		i;

	x = e->users[cs]->player.x;
	y = e->users[cs]->player.y;
	lvl = e->users[cs]->player.lvl;
	good = 1;
	i = 0;
	while (++i < NB_STONE + 1)
		if (e->map[y][x].ground[i] < g_lvlup[lvl - 1][i])
			good = -1;
	if (good == 1)
		good = check_lvl_users(e, cs, x, y);
	if (good == 1)
		e->users[cs]->player.lvlup_good = 1;
	if (last_inc(e, cs) == 1)
		end_incant(e, cs, good);
}

static int		verify_cmd(t_user *user)
{
	int			ar;
	t_actions	*act;

	ar = user->player.cur_aread;
	act = &user->player.acts[ar];
	if (act->time != 0 && act->fct_cmd == move_forward)
		return (0);
	if (act->time != 0 && act->fct_cmd == turn_left)
		return (0);
	if (act->time != 0 && act->fct_cmd == turn_right)
		return (0);
	return (1);
}

void			make_incantations(t_env *e, int cs)
{
	int		x;
	int		y;
	t_user	*tmp;
	double	time;
	int		ar;

	x = e->users[cs]->player.x;
	y = e->users[cs]->player.y;
	tmp = e->map[y][x].player;
	ar = e->users[cs]->player.cur_aread;
	time = e->users[cs]->player.acts[ar].time;
	while (tmp != NULL)
	{
		if ((tmp->started && e->users[cs]->player.lvl == tmp->player.lvl
			&& verify_cmd(tmp) == 1) || cs == tmp->sock)
		{
			if (tmp->sock != cs)
				remove_actions(tmp, time);
			tmp->player.lvlup = 1;
			tmp_to_bc(&tmp->buf_write, "elevation en cours", 1);
		}
		tmp = tmp->next;
	}
	gfx_send_npc(e, cs, gfx_pic);
}
