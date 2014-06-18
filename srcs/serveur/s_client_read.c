/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_client_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/17 16:58:15 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/18 22:35:20 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "serveur.h"
#include "libft.h"

void	ma_fct_cmd(t_env *e, int cs);

t_ponf_cmd	g_tab[NBR_CMD] =
{
	{"avance", 7, move_forward, gfx_move_forward},
	{"droite", 7, turn_right, gfx_turn_right},
	{"gauche", 7, turn_left, gfx_turn_left},
	{"voir", 7, watch_sight, NULL},
	{"inventaire", 1, send_inv, NULL},
	{"prend", 7, take_item, NULL},
	{"pose", 7, drop_item, NULL},
	{"expulse", 7, expulse, NULL},
	{"broadcast", 7, broadcast, NULL},
	{"incantation", 300, incantation, NULL},
	{"fork", 42, my_fork, NULL},
	{"connect_nbr", 0, connect_nbr, NULL},
	{"-", 0, ma_fct_cmd, NULL}
};

int		accept_gamer(t_env *e, int cs, int nb_left)
{
	char		*tmp;
	int			i;

	i = -1;
	e->users[cs]->ig = 1;
	e->users[cs]->player.team = ft_strdup(e->users[cs]->buf_read_tmp);
	init_player(e, cs);
	e->users[cs]->player.cur_aread = 0;
	while (++i < 10)
		e->users[cs]->player.acts[i].time = 0;
	tmp = ft_itoa(nb_left);
	tmp_to_bc(&e->users[cs]->buf_write, tmp, 1);
	free(tmp);
	tmp = ft_itoa(e->opt.x);
	tmp_to_bc(&e->users[cs]->buf_write, tmp, 0);
	free(tmp);
	char_to_bc(&e->users[cs]->buf_write, ' ');
	tmp = ft_itoa(e->opt.y);
	tmp_to_bc(&e->users[cs]->buf_write, tmp, 1);
	free(tmp);
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
			j = accept_gamer(e, cs, e->team[i].member);
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
	tmp_to_bc(&e->users[cs]->buf_write, "Not down yet", 1);
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
		acts[i].time = 0;
	read = user->player.cur_aread;
	acts[read].time = time;
	acts[read].fct_cmd = g_tab[9].fct_cmd;
	user->player.cur_awrite = (read + 1) % 10;
}

void	make_incantations(t_env *e, int cs, double time)
{
	int		x;
	int		y;
	t_user	*tmp;

	x = e->users[cs]->player.x;
	y = e->users[cs]->player.y;
	tmp = e->map[x][y].player;
	while (tmp != NULL)
	{
		if (e->users[cs]->player.lvl == tmp->player.lvl)
		{
			if (tmp->sock != cs)
				remove_actions(tmp, time);
			tmp_to_bc(&tmp->buf_write, "elevation en cours", 1);
		}
		tmp = tmp->next;
	}
}

void	queue_actions(t_env *e, int cs)
{
	int		i;
	double	time;
	int		j;
	char	**cmd;
	int		ca;

	time = ft_usec_time();
	cmd = ft_strsplit(e->users[cs]->buf_read_tmp, '\n');
	i = -1;
	ca = e->users[cs]->player.cur_awrite;
	while (cmd[++i] && e->users[cs]->player.acts[ca].time == 0)
	{
		ca = e->users[cs]->player.cur_awrite;
		j = get_action_value(cmd[i]);
		if (j != -1)
		{
			time = time + ((double)g_tab[j].value * 1000000) / (double)e->opt.time;
			
			e->users[cs]->player.acts[ca].time = time;
			e->users[cs]->player.acts[ca].cmd = get_cmd_arg(cmd[i]);
			if (j == 9)
				make_incantations(e, cs, time);
			e->users[cs]->player.acts[ca].fct_cmd = g_tab[j].fct_cmd;
			if (g_tab[j].fct_gfx)
				g_tab[j].fct_gfx(e, cs);
			e->users[cs]->player.cur_awrite = (ca + 1) % 10;
		}
		else
			tmp_to_bc(&e->users[cs]->buf_write, "KO", 1);
	}
	ft_bzero(e->users[cs]->buf_read_tmp, 40960); // 40960 ?
	ft_tabdel(&cmd);
}

void	make_cmd(t_env *e, int cs)
{
	if (e->users[cs]->ig != 1)
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
			if (e->users[cs]->gfx.gfx)
			{
				printf("Received gfx: [%s]", e->users[cs]->buf_read_tmp);
				//				gfx_cmd
			}
			else
			{
				printf("Receive from %d : %s", cs, e->users[cs]->buf_read_tmp);
				make_cmd(e, cs);
			}
			e->users[cs]->buf_read_tmp[0] = '\0';
		}
	}
}
