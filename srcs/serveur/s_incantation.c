/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_incantation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/16 18:09:14 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/22 18:04:36 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>

static int		g_lvlup[7][8] = {
	{0, 1, 0, 0, 0, 0, 0, 1},
	{0, 1, 1, 1, 0, 0, 0, 2},
	{0, 2, 0, 1, 0, 2, 0, 2},
	{0, 1, 1, 2, 0, 1, 0, 4},
	{0, 1, 2, 1, 3, 0, 0, 4},
	{0, 1, 2, 3, 0, 1, 0, 6},
	{0, 2, 2, 2, 2, 2, 1, 6}
};

static void	disperse_stone(t_env *e, int cs)
{
	int		nb;
	int		nb_stone;
	int		i;
	int		x;
	int		y;

	nb = e->users[cs]->player.lvl - 1;
	i = 1;
	while (i < 7)
	{
		x = e->users[cs]->player.x;
		y = e->users[cs]->player.y;
		nb_stone = g_lvlup[nb][i];
		while (nb_stone != 0)
		{
			e->map[x][y].ground[i]--;
			x = rand() % e->opt.x;
			y = rand() % e->opt.y;
			e->map[x][y].ground[i]++;
			gfx_send_map(e, x, y, gfx_bct);
			nb_stone--;
		}
		i++;
	}
	e->users[cs]->player.acts[e->users[cs]->player.cur_aread].start = 0;
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
	if (good == 1)
		(*lvl)++;
	if (good == 1 && e->users[cs]->player.acts[
			e->users[cs]->player.cur_aread].start == 1)
		disperse_stone(e, cs);
	char_to_bc(&e->users[cs]->buf_write, '0' + *lvl);
	tmp_to_bc(&e->users[cs]->buf_write, "", 1);
	if (e->users[cs]->player.inc == 1)
	{
		e->users[cs]->player.inc = 0;
		gfx_send_act(e, cs, gfx_pie, good);// send all infos to gfxs pce etc
	}
}

int		verify_cmd(t_user *user)
{
	(void)user;
	return (1);
}

void	make_incantations(t_env *e, int cs)
{
	int		x;
	int		y;
	t_user	*tmp;
	double	time;
	int		aw;

	x = e->users[cs]->player.x;
	y = e->users[cs]->player.y;
	e->users[cs]->player.inc = 1;
	tmp = e->map[x][y].player;
	aw = e->users[cs]->player.cur_awrite;
	time = e->users[cs]->player.acts[aw].time;
	while (tmp != NULL)
	{
		if (e->users[cs]->player.lvl == tmp->player.lvl && verify_cmd(tmp) == 1)
		{
			if (tmp->sock != cs)
				remove_actions(tmp, time);
			e->users[cs]->player.acts[e->users[cs]->player.cur_awrite].start = 1;
			tmp_to_bc(&tmp->buf_write, "elevation en cours", 1);
		}
		tmp = tmp->next;
	}
	gfx_send_npc(e, cs, gfx_pic);
}
