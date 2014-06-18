/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_serveur_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/17 21:25:21 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/17 22:49:36 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>

void	fork_one_user(t_env *e)
{
	if (fork() == 0)
		execve("./client", e->av, NULL);
}

void	launch_new_clt(t_env *e)
{
	if (e->user->buf_read_tmp[0] > '0')
		fork_one_user(e);
}

void	size_map(t_env *e)
{
	char	*p_x;
	char	*p_y;
	t_map	**view;
	int		i;

	i = -1;
	p_x = ft_strchr(e->user->buf_read_tmp, '\n') + 1;
	p_y = ft_strchr(p_x, ' ') + 1;
	e->me.x = ft_atoi(p_x);
	e->me.y = ft_atoi(p_y);
	view = (t_map **)XV(NULL, malloc(sizeof(t_map *) * (e->me.x)), "malloc");
	while (++i < e->me.x)
	{
		view[i] = (t_map *)XV(NULL, malloc(sizeof(t_map)), "malloc");
		bzero(view, sizeof(t_map));
	}
	e->user->player.ia.view = view;
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

void	queue_actions(t_env *e)
{
	int				a_read;
	t_actions		*acts;

	a_read = e->user->player.cur_aread;
	acts = e->user->player.acts;
	acts[a_read].cmd = ft_strdup(e->user->buf_read_tmp);
	acts[a_read].fct_cmd(e);
	acts[a_read].time = 0;
	e->user->player.cur_aread = (e->user->player.cur_aread + 1) % 10;
}

void	make_cmd(t_env *e)
{
	if (e->user->ig == 0)
		ask_to_play(e);
	else
		queue_actions(e);
}

voidq	rcv_serveur(t_env *e)
{
	int		r;

	r = recv(e->user->sock, e->user->buf_read_tmp, BC_SIZE, 0);
	if (r <= 0)
	{
		close(e->user->sock);
		exit(0);
	}
	e->user->buf_read_tmp[r] = '\0';
	tmp_to_bc(&e->user->buf_read, e->user->buf_read_tmp, 0);
	e->user->buf_read_tmp[0] = '\0';
	if (verify_bsn(&e->user->buf_read) == 1)
	{
		bc_to_tmp(&e->user->buf_read, e->user->buf_read_tmp);
		printf("Receive : %s", e->user->buf_read_tmp);
		make_cmd(e);
		e->user->buf_read_tmp[0] = '\0';
	}
}
