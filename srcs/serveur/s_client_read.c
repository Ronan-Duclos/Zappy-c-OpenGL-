/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_client_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 20:06:47 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/13 12:23:20 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "serveur.h"
#include "libft.h"

void	ma_fct_cmd(t_env *e, int cs);

t_ponf_cmd	g_tab[NBR_CMD] =
{
	{"avance", 7, moove_forward},
	{"droite", 7, turn_right},
	{"gauche", 7, turn_left},
	{"voir", 7, ma_fct_cmd},
	{"inventaire", 1, ma_fct_cmd},
	{"prend", 7, ma_fct_cmd},
	{"pose", 7, ma_fct_cmd},
	{"expulse", 7, ma_fct_cmd},
	{"broadcast", 7, ma_fct_cmd},
	{"incantation", 300, ma_fct_cmd},
	{"fork", 42, ma_fct_cmd},
	{"connect_nbr", 0, ma_fct_cmd},
	{"-", 0, ma_fct_cmd},
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

	i = 0;
	j = 0;
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

int		get_action_value(char *cmd, void (*fct_cmd)())
{
	int	i;

	i = 0;
	while (i < NBR_CMD && !ft_strequ(cmd, g_tab[i].str))
		i++;
	if (i == NBR_CMD)
		printf("bad command : %s\n", cmd);
	fct_cmd = g_tab[i].fct_cmd;
	return (g_tab[i].value);
	fct_cmd(NULL, 1);
	return (0);
}

void	ma_fct_cmd(t_env *e, int cs)
{
	ft_putendl("MERDE CACA BOITE COUCOU");
	if (e->users[cs]->player.direc == NORTH)
		e->users[cs]->player.y++;
	tmp_to_bc(&e->users[cs]->buf_write, "OK", 1);
}

void	queue_actions(t_env *e, int cs)
{
	int		i;
	double	time;
	double	tmp_time;
	char	**cmd;

	time = ft_usec_time();
	cmd = ft_strsplit(e->users[cs]->buf_read_tmp, '\n');
	i = -1;
	while (cmd[++i])
	{
		tmp_time = get_action_value(cmd[i], e->users[cs]->player.acts[i].fct_cmd);
		time += tmp_time * 1000000 / e->opt.time;
		e->users[cs]->player.acts[i].time = time;
		e->users[cs]->player.acts[i].cs = cs;
		e->users[cs]->player.acts[i].fct_cmd = ma_fct_cmd;
	}
	ft_bzero(e->users[cs]->buf_read_tmp, 40960);
	ft_tabdel(&cmd);
}

void	make_cmd(t_env *e, int cs)
{
	char	*tmp;

	tmp = ft_strchr(e->users[cs]->buf_read_tmp, '\n');
	tmp[0] = '\0';
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
