/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_incantation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/16 18:09:14 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/27 08:50:01 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>
#include <libft.h>
#include <global.h>

static void		disperse_stone(t_env *e, int cs, int good)
{
	int		nb_stone;
	int		i;
	int		x;
	int		y;

	if (good != 1)
		return ;
	i = 0;
	while (++i < 7)
	{
		x = e->users[cs]->player.x;
		y = e->users[cs]->player.y;
		nb_stone = g_lvlup[e->users[cs]->player.lvl - 1][i];
		while (nb_stone != 0)
		{
			if (e->map[y][x].ground[i] > 0)
				e->map[y][x].ground[i]--;
			x = rand() % e->opt.x;
			y = rand() % e->opt.y;
			e->map[y][x].ground[i]++;
			gfx_send_map(e, x, y, gfx_bct);
			nb_stone--;
		}
	}
	e->users[cs]->player.acts[e->users[cs]->player.cur_aread].start = 0;
}

void			end_incant(t_env *e, int cs, int good)
{
	int		x;
	int		y;
	int		id;
	t_inc	*tmp;
	int		i;

	id = e->users[cs]->player.lvlup;
	tmp = e->incs;
	while (tmp && tmp->id != id)
		tmp = tmp->next;
	if (tmp != NULL)
	{
		i = 0;
		while (tmp->css[i] != 0)
		{
			e->users[tmp->css[i]]->player.end_inc = 0;
			i++;
		}
	}
	remove_incs(e, id);
	x = e->users[cs]->player.x;
	y = e->users[cs]->player.y;
	gfx_send_act(e, cs, gfx_pie, good);
	disperse_stone(e, cs, good);
	gfx_send_map(e, x, y, gfx_bct);
	e->users[cs]->player.inc = 0;
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
	while (tmp && tmp->next != NULL)
	{
		if (tmp->sock > sock)
			sock = tmp->sock;
		tmp = tmp->next;
	}
	if (tmp->sock == cs)
		return (1);
	return (0);
}

int				check_users_lvl(t_env *e, int cs)
{
	int			good;
	int			x;
	int			y;
	t_user		*tmp;
	int			lvlup;

	good = 0;
	x = e->users[cs]->player.x;
	y = e->users[cs]->player.y;
	tmp = e->map[y][x].player;
	lvlup = e->users[cs]->player.lvlup;
	tmp->player.end_inc = 1;
	while (tmp != NULL)
	{
		if (tmp->player.lvlup == lvlup)
			good++;
		tmp = tmp->next;
	}
	printf("NB PLAYER TO LVLUP : [%d]\n", g_lvlup[e->users[cs]->player.lvl - 1][_player]);
	if (good >= g_lvlup[e->users[cs]->player.lvl - 1][_player])
		return (1);
	return (-1);
}

void			incantation(t_env *e, int cs)
{
	int		x;
	int		y;
	int		*lvl;
	int		good;
	int		i;

	x = e->users[cs]->player.x;
	y = e->users[cs]->player.y;
	lvl = &e->users[cs]->player.lvl;
	good = 1;
	i = 0;
	while (++i < NB_STONE + 2)
		if (e->map[y][x].ground[i] < g_lvlup[*lvl - 1][i])
			good = -1;
	good = check_users_lvl(e, cs);
	if (good == 1 && last_inc(e, cs) == 1)
		end_incant(e, cs, good);
	printf("Client AVANT [%d] level up to %d\n", cs, *lvl);
	if (good == 1)
		(*lvl)++;
	printf("Client APRES [%d] level up to %d\n", cs, *lvl);
	gfx_send_npc(e, cs, gfx_plv);
	char_to_bc(&e->users[cs]->buf_write, '0' + *lvl);
	tmp_to_bc(&e->users[cs]->buf_write, "", 1);
}

static int		verify_cmd(t_user *user)
{
	int			ar;
	t_actions	*act;

	ar = user->player.cur_aread;
	act = &user->player.acts[ar];
	if (act->time != 0 && act->fct_cmd == &move_forward)
		return (0);
	if (act->time != 0 && act->fct_cmd == &turn_left)
		return (0);
	if (act->time != 0 && act->fct_cmd == &turn_right)
		return (0);
	return (1);
}

int				find_incantation_id(t_env *e, int cs)
{
	t_inc	*tmp;
	int		i;

	tmp = e->incs;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->css[i] != 0)
		{
			if (tmp->css[i] == cs)
			{
					e->users[cs]->player.lvlup = tmp->id;
					return (tmp->id);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (-1);
}

double			find_incantation_time(t_env *e, int cs)
{
	int		id;
	t_inc	*inc;

	id = e->users[cs]->player.lvlup;
	inc = e->incs;
	while (inc != NULL)
	{
		if (inc->id == id)
			return (inc->time);
		inc = inc->next;
	}
	return (0);
}

void			make_incantations(t_env *e, int cs)
{
	int				x;
	int				y;
	int				id;
	t_user			*tmp;
	double			time;

	x = e->users[cs]->player.x;
	y = e->users[cs]->player.y;
	e->users[cs]->player.inc = 1;
	tmp = e->map[y][x].player;
	id = find_incantation_id(e, cs);
	time = find_incantation_time(e, cs);
	printf("PLAYER [%d] LVL AT : x [%d], y [%d], : %f\n", cs, x, y, time);
	while (tmp != NULL)
	{
		if (tmp->started && e->users[cs]->player.lvl == tmp->player.lvl
			&& verify_cmd(tmp) == 1 && (tmp->player.lvlup == 0 || tmp->sock == cs)
		{
			if (tmp->sock != cs)
			{
				remove_actions(tmp, time);
				tmp->player.lvlup = id;
				add_css_lc(e, tmp->sock, id);
			}
			tmp_to_bc(&tmp->buf_write, "elevation en cours", 1);
		}
		tmp = tmp->next;
	}
	gfx_send_npc(e, cs, gfx_pic);
}
