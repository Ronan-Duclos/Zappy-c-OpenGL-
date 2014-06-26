/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_incantation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/16 18:09:14 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/26 23:11:39 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>
#include <libft.h>

static int		g_lvlup[7][8] = {
	{0, 1, 0, 0, 0, 0, 0, 1},
	{0, 1, 1, 1, 0, 0, 0, 2},
	{0, 2, 0, 1, 0, 2, 0, 2},
	{0, 1, 1, 2, 0, 1, 0, 4},
	{0, 1, 2, 1, 3, 0, 0, 4},
	{0, 1, 2, 3, 0, 1, 0, 6},
	{0, 2, 2, 2, 2, 2, 1, 6}
};

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
			e->map[x][y].ground[i]--;
			x = rand() % e->opt.x;
			y = rand() % e->opt.y;
			e->map[x][y].ground[i]++;
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

	x = e->users[cs]->player.x;
	y = e->users[cs]->player.y;
	gfx_send_act(e, cs, gfx_pie, good);
	disperse_stone(e, cs, good);
	gfx_send_map(e, x, y, gfx_bct);
	e->users[cs]->player.inc = 0;
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
	while (++i < NB_STONE + 1)
		if (e->map[x][y].ground[i] < g_lvlup[*lvl - 1][i])
			good = -1;
	if (good == 1 && e->users[cs]->player.inc == 1)
		end_incant(e, cs, good);
	if (good == 1)
		(*lvl)++;
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
	if (act->time != 0 || act->fct_cmd == move_forward)
		return (0);
	if (act->fct_cmd == turn_left)
		return (0);
	if (act->fct_cmd == turn_right)
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
	e->users[cs]->player.inc = 1;
	tmp = e->map[x][y].player;
	ar = e->users[cs]->player.cur_aread;
	time = e->users[cs]->player.acts[ar].time;
	while (tmp != NULL)
	{
		if ((e->users[cs]->player.lvl == tmp->player.lvl
			&& verify_cmd(tmp) == 1) || cs == tmp->sock)
		{
			if (tmp->sock != cs)
				remove_actions(tmp, time);
			tmp_to_bc(&tmp->buf_write, "elevation en cours", 1);
		}
		tmp = tmp->next;
	}
	gfx_send_npc(e, cs, gfx_pic);
}
