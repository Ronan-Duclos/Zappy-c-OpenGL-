/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_serveur_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/17 21:25:21 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/27 08:38:10 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>

void	fork_one_user(t_env *e)
{
	static int		i;

	if (i == 0 && (i = 1) == 1 && fork() == 0)
	{
		close(e->user->sock);
		execve(e->av[0], e->av, NULL);
	}
}

void	launch_new_clt(t_env *e)
{
	printf("[retourconnect nbr] %s\n", e->user->buf_read_tmp);
	if (atoi(e->user->buf_read_tmp) > 0)
		fork_one_user(e);
}

void	size_map(t_env *e)
{
	char	*p_x;
	char	*p_y;

	p_x = ft_strchr(e->user->buf_read_tmp, '\n') + 1;
	p_y = ft_strchr(p_x, ' ') + 1;
	e->me.x = ft_atoi(p_x);
	e->me.y = ft_atoi(p_y);
}

void	ask_to_play(t_env *e)
{
	static int		i;

	if (i == 0)
	{
		tmp_to_bc(&e->user->buf_write, e->me.name, 1);
		i++;
	}
	else
	{
		launch_new_clt(e);
		size_map(e);
		e->user->player.ia.x = e->me.x / 2;
		e->user->player.ia.y = e->me.y / 2;
		e->user->ig = 1;
	}
}

int		verify_word(char *str, char *cmp)
{
	int		i;

	i = -1;
	while (str[++i] != '\0' && cmp[i] != '\0')
	{
		if (str[i] != cmp[i])
			return (-1);
	}
	if (cmp[i] != '\0')
		return (-1);
	return (0);
}

void	queue_actions(t_env *e)
{
	int				a_read;
	t_actions		*acts;
	char			*tmp;

	if (verify_word(e->user->buf_read_tmp, "deplacement") != 0)
	{
		a_read = e->user->player.cur_aread;
		acts = e->user->player.acts;
		acts[a_read].answer = ft_strdup(e->user->buf_read_tmp);
		acts[a_read].fct_cmd(e);
		if (acts[a_read].answer)
			free(acts[a_read].answer);
		if (acts[a_read].cmd != NULL)
			free(acts[a_read].cmd);
		acts[a_read].cmd = NULL;
		acts[a_read].answer = NULL;
		acts[a_read].time = 0;
		e->user->player.cur_aread = (e->user->player.cur_aread + 1) % 10;
	}
	else
	{
		tmp = ft_strchr(e->user->buf_read_tmp, ' ') + 1;
		e->user->player.ia.expulsed = ft_atoi(tmp);
	}
}

void	replace_calendar(t_env *e)
{
	int		i;

	i = -1;
	while (++i < 10)
	{
		e->user->player.acts[i].time = 0;
		if (e->user->player.acts[i].cmd != NULL)
			free(e->user->player.acts[i].cmd);
	e->user->player.acts[i].cmd = NULL; // rajout robin double free;
		if (e->user->player.acts[i].answer != NULL)
			free(e->user->player.acts[i].answer);
	e->user->player.acts[i].answer = NULL; // rajout robin double free;
	}
	e->user->player.cur_aread = 0;
	e->user->player.cur_awrite = 1;
	e->user->player.acts[0].cmd = ft_strdup("incantation");
	e->user->player.acts[0].time = 1;
	e->user->player.ia.lvlup = 1;
	e->user->player.acts[0].fct_cmd = incantation;
	while (e->user->player.ia.todo)
		del_todo(e);
}

void	receive_broadcast(t_env *e)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strchr(e->user->buf_read_tmp, ' ') + 1;
	if (!tmp1)
		return ;
	tmp1[1] = '\0';
	tmp2 = tmp1 + 2;
	if (e->user->player.ia.lvlup != 1 && ft_atoi(tmp2) == e->user->player.ia.lvl)
	{
		e->user->player.ia.bdc = ft_atoi(tmp1);
		e->user->player.ia.msg = ft_strdup(tmp2);
	}
}

void	make_cmd(t_env *e)
{
	int		i;
	char	**cmd;

	i = -1;
	if (e->user->ig == 0)
		ask_to_play(e);
	else
	{
		cmd = ft_strsplit(e->user->buf_read_tmp, '\n');
		while (cmd[++i] != NULL)
		{
			ft_strcpy(e->user->buf_read_tmp, cmd[i]);
			if (verify_word(e->user->buf_read_tmp, "elevation en cours") == 0)
				replace_calendar(e);
			else if (verify_word(e->user->buf_read_tmp, "message") == 0)
				receive_broadcast(e);
			else if (verify_word(e->user->buf_read_tmp, "mort") == 0)
			{
				printf("t mort boule\n");
				exit(0);
			}
			else
				queue_actions(e);
		}
		ft_tabdel(&cmd);
	}
}

void	rcv_serveur(t_env *e)
{
	int		r;

	r = recv(e->user->sock, e->user->buf_read_tmp, BC_SIZE, 0);
	if (r <= 0)
	{
		close(e->user->sock);
		exit(0);
	}
	e->user->buf_read_tmp[r] = '\0';
	if(death_clt(e) == 0)
	{
		tmp_to_bc(&e->user->buf_read, e->user->buf_read_tmp, 0);
		if (verify_bsn(&e->user->buf_read) == 1)
		{
			bc_to_tmp(&e->user->buf_read, e->user->buf_read_tmp);
			if (e->me.v)
				printf("\033[33mReceive : \033[0m%s", e->user->buf_read_tmp);
			make_cmd(e);
		}
	}
	e->user->buf_read_tmp[0] = '\0';
}
