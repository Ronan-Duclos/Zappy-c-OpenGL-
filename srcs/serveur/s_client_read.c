/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_client_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 20:06:47 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/13 23:23:29 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "serveur.h"
#include "libft.h"

void	ma_fct_cmd(t_env *e, int cs);

t_ponf_cmd	g_tab[NBR_CMD] =
{
	{"avance", 7, move_forward},
	{"droite", 7, turn_right},
	{"gauche", 7, turn_left},
	{"voir", 7, ma_fct_cmd},
	{"inventaire", 1, send_inv},
	{"prend", 7, take_item},
	{"pose", 7, ma_fct_cmd},
	{"expulse", 7, ma_fct_cmd},
	{"broadcast", 7, ma_fct_cmd},
	{"incantation", 300, ma_fct_cmd},
	{"fork", 42, ma_fct_cmd},
	{"connect_nbr", 0, ma_fct_cmd},
	{"-", 0, ma_fct_cmd}
};

int		accept_gamer(t_env *e, int cs)
{
	char		*tmp;
	int			i;

	i = -1;
	e->users[cs]->ig = 1;
	e->users[cs]->player.team = ft_strdup(e->users[cs]->buf_read_tmp);
	e->users[cs]->player.cur_aread = 0;
	while (++i < 10)
		e->users[cs]->player.acts[i].time = 0;
	tmp = ft_itoa(cs);
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

	i = 0;
	j = 0;
	tmp = ft_strchr(e->users[cs]->buf_read_tmp, '\n');
	tmp[0] = '\0';
	if (!ft_strcmp(e->users[cs]->buf_read_tmp, "GRAPHIC"))
	{
		gfx_init(e, cs);
		return ;
	}
	while (e->opt.name[i] != NULL)
	{
		if (ft_strcmp(e->users[cs]->buf_read_tmp, e->opt.name[i]) == 0)
			j = accept_gamer(e, cs);
		i++;
	}
	if (j == 0)
	{
		close(cs);
		destroy_clt(e, cs);
	}
}

int		get_action_value(char *cmd)
{
	int	i;

	i = 0;
	while (i < NBR_CMD && !ft_strncmp(cmd, g_tab[i].str, ft_strlen(cmd)))
		i++;
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
	int		i;
	int		j;
	char		*ret;

	i = 0;
	j = 0;
	ret = NULL;
	while (cmd[i] && cmd[i] != '<')
		i++;
	if (cmd[i])
		j = i + 1;
	else 
		return (NULL);
	while (cmd[i] && cmd[i] != '>')
		i++;
	if (cmd[i])
	{
		cmd[i] = 0;
		ret = ft_strdup(cmd + j);
	}
	return (ret);
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
			e->users[cs]->player.acts[ca].fct_cmd = g_tab[i].fct_cmd;
			e->users[cs]->player.cur_awrite = (ca + 1) % 10;
		}
	}
	ft_bzero(e->users[cs]->buf_read_tmp, 40960);
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
			if (e->users[cs]->gfx)
			{
				printf("Received gfx: [%s]", e->users[cs]->buf_read_tmp);
				//				gfx_cmd
			}
			else
			{
				printf("Receive : %s", e->users[cs]->buf_read_tmp);
				make_cmd(e, cs);
			}
			e->users[cs]->buf_read_tmp[0] = '\0';
		}
	}
}
