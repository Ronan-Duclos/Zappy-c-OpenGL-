/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_client_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/17 16:58:15 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/24 12:47:39 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "serveur.h"
#include "libft.h"

t_ponf_cmd	g_tab[NBR_CMD] =
{
	{"avance", 7, move_forward, gfx_move_forward},
	{"droite", 7, turn_right, gfx_turn_right},
	{"gauche", 7, turn_left, gfx_turn_left},
	{"voir", 7, watch_sight, NULL},
	{"inventaire", 1, send_inv, NULL},
	{"prend", 7, take_item, gfx_take_item},
	{"pose", 7, drop_item, gfx_drop_item},
	{"expulse", 7, expulse, NULL},
	{"broadcast", 7, broadcast, NULL},
	{"incantation", 300, incantation, make_incantations},
	{"fork", 42, my_fork, gfx_fork},
	{"connect_nbr", 0, connect_nbr, NULL}
};

void	send_start(t_env *e, int cs)
{
	char			*nb_connect;
	int				*ar;
	char			buf[25];

	ar = &e->users[cs]->player.cur_aread;
	nb_connect = e->users[cs]->player.acts[*ar].cmd;
	tmp_to_bc(&e->users[cs]->buf_write, nb_connect, 1);
	sprintf(buf, "%d %d", e->opt.x, e->opt.y);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
	e->users[cs]->player.acts[*ar].time = 0;
	gfx_send_npc(e, cs, gfx_pnw);
//	*ar = (*ar + 1 ) % 10;
}

int		accept_gamer(t_env *e, int cs, int team)
{
	int			i;

	e->users[cs]->ig = 1;
	e->users[cs]->player.team = ft_strdup(e->users[cs]->buf_read_tmp);
	e->users[cs]->player.cur_aread = 0;
	e->users[cs]->player.cur_awrite = 0;
	i = -1;
	while (++i < 10)
	{
		e->users[cs]->player.acts[i].time = 0;
		e->users[cs]->player.acts[i].start = 0;
	}
	init_player(e, cs, team);
	return (1);
}

void	check_team(t_env *e, int cs)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = 0;
	tmp = ft_strchr(e->users[cs]->buf_read_tmp, '\n');
	tmp[0] = '\0';
	if (!ft_strcmp(e->users[cs]->buf_read_tmp, "GRAPHIC"))
	{
		gfx_init(e, cs);
		return ;
	}
	while (e->opt.name[++i] != NULL)
		if (ft_strcmp(e->users[cs]->buf_read_tmp, e->team[i].name) == 0
			&& e->team[i].member != 0)
		{
			e->team[i].member--;
			j = accept_gamer(e, cs, i);
		}
	if (j == 0)
	{
		close(cs);
		destroy_clt(e, cs);
	}
}

int		get_action_value(char *cmd)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(g_tab[i].str);
	while (i < NBR_CMD && ft_strncmp(cmd, g_tab[i].str, j) != 0)
		j = ft_strlen(g_tab[++i].str);
	if (i == NBR_CMD)
	{
		printf("bad command : %s\n", cmd);
		return (-1);
	}
	return (i);
}

void	ma_fct_cmd(t_env *e, int cs)
{
	tmp_to_bc(&e->users[cs]->buf_write, "Not done yet", 1);
}

char	*get_cmd_arg(char *cmd)
{
	int			i;
	char		*ret;

	i = 0;
	ret = NULL;
	while (cmd[i] != '\0' && cmd[i] != ' ')
		i++;
	if (cmd[i] != '\0')
		i++;
	else
		return (NULL);
	ret = ft_strdup(cmd + i);
	return (ret);
}

void	remove_actions(t_user *user, double time)
{
	t_actions	*acts;
	int			read;
	int			i;

	i = -1;
	acts = user->player.acts;
	while (++i < 10)
	{
		acts[i].time = 0;
		if (acts[i].cmd != NULL)
			free(acts[i].cmd);
		acts[i].cmd = NULL;
	}
	user->player.cur_aread = 0;
	user->player.cur_awrite = 0;
	read = 0;
	printf("rem_act: %f\n", time);
	acts[read].time = time;
	acts[read].fct_cmd = g_tab[9].fct_cmd;
	user->player.cur_awrite = 1;
}

void	start_action(t_env *e, int cs)
{
	int		st;

	st = e->users[cs]->player.cur_awrite;
	if (st == 0 && e->users[cs]->player.acts[9].time != 0)
		e->users[cs]->player.acts[0].start = e->users[cs]->player.acts[9].time;
	else if (st != 0)
		e->users[cs]->player.acts[st].start = e->users[cs]->player.acts[st - 1].time;
	else
		e->users[cs]->player.acts[st].start = ft_usec_time();
}

/*
**	Add By clem to update calendar start time before adding in it.
*/
static double	get_start_time(t_env *e, int cs, int ca)
{
	double	time;

	time = e->users[cs]->player.acts[ca].start;
	if (!time)
	{
		time = ft_usec_time();
		e->users[cs]->player.acts[ca].start = time;
	}
	return (time);
}

void	queue_actions(t_env *e, int cs)
{
	int		i;
	double	time;
	int		j;
	char	**cmd;
	int		ca;

	start_action(e, cs);
	cmd = ft_strsplit(e->users[cs]->buf_read_tmp, '\n');
	i = -1;
	ca = e->users[cs]->player.cur_awrite;
	time = get_start_time(e, cs, ca);
	while (cmd[++i] && e->users[cs]->player.acts[ca].time == 0)
	{
		ca = e->users[cs]->player.cur_awrite;
		j = get_action_value(cmd[i]);
		if (j != -1)
		{
			time = time + ((double)g_tab[j].value * 1000000) / (double)e->opt.time;
			if (time < e->srv.time)
				e->srv.time = time;
			e->users[cs]->player.acts[ca].time = time;
			e->users[cs]->player.acts[ca].cmd = get_cmd_arg(cmd[i]);
			e->users[cs]->player.acts[ca].fct_cmd = g_tab[j].fct_cmd;
			e->users[cs]->player.acts[ca].fct_gfx = g_tab[j].fct_gfx;
			e->users[cs]->player.cur_awrite = (ca + 1) % 10;
		}
		else
			tmp_to_bc(&e->users[cs]->buf_write, "KO", 1);
	}
	bzero(e->users[cs]->buf_read_tmp, BC_SIZE);
	ft_tabdel(&cmd);
}

void	make_cmd(t_env *e, int cs)
{
	if (e->users[cs]->gfx.gfx)
		gfx_cmd_check(e, cs, e->users[cs]->buf_read_tmp);
	else if (e->users[cs]->ig != 1)
		check_team(e, cs);
	else if (e->users[cs]->type == FD_CLT)
		queue_actions(e, cs);
}

void	client_read(t_env *e, int cs)
{
	int		r;

	r = recv(cs, e->users[cs]->buf_read_tmp, BC_SIZE, 0);
	if (r <= 0)
	{
		if (!e->users[cs]->gfx.gfx)
			gfx_send_npc(e, cs, gfx_pdi);
		close(cs);
		destroy_clt(e, cs);
	}
	else
	{
		e->users[cs]->buf_read_tmp[r] = '\0';
		tmp_to_bc(&e->users[cs]->buf_read, e->users[cs]->buf_read_tmp, 0);
		if (verify_bsn(&e->users[cs]->buf_read) == 1)
		{
			bc_to_tmp(&e->users[cs]->buf_read, e->users[cs]->buf_read_tmp);
			printf("Receive from %d : %s", cs, e->users[cs]->buf_read_tmp);
			make_cmd(e, cs);
			e->users[cs]->buf_read_tmp[0] = '\0';
		}
	}
}
