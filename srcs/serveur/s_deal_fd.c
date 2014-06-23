/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_deal_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 20:06:02 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/23 18:02:42 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <conf.h>
#include "libft.h"
#include <serveur.h>

void	clear_player(t_env *e, int cs)
{
	int		i;

	i = -1;
	remove_user_on_map(e, cs);
	while (e->opt.name[++i] != NULL)
	{
		if (ft_strcmp(e->team[i].name, e->users[cs]->player.team) == 0)
			e->team[i].member++;
	}
}

void	create_clt(t_env *e, int s)
{
	int						cs;
	unsigned int			len;
	struct sockaddr_in		clt;

	cs = X(-1, accept(s, (struct sockaddr *)&clt, &len), "accepte");
	e->users[cs]->type = FD_CLT;
	e->users[cs]->sock = cs;
	e->users[cs]->fct_read = client_read;
	e->users[cs]->fct_write = client_write;
	bzero(&e->users[cs]->player, sizeof(t_player));
	tmp_to_bc(&e->users[cs]->buf_write, "BIENVENUE", 1);
	printf("Client connected : %d\n", cs);
}

void	destroy_clt(t_env *e, int sock)
{
	if (e->users[sock]->ig == 1 && !e->users[sock]->gfx.gfx)
		clear_player(e, sock);
	if (e->users[sock]->player.team != NULL)
		free(e->users[sock]->player.team);
	e->users[sock]->player.team = NULL;
	init_bc(&e->users[sock]->buf_read);
	init_bc(&e->users[sock]->buf_write);
	e->users[sock]->buf_read_tmp[0] = '\0';
	e->users[sock]->buf_write_tmp[0] = '\0';
	if (e->users[sock]->gfx.gfx)
		glst_del_one(&e->srv.glst, sock);
	bzero(&e->users[sock]->gfx, sizeof(t_gfx));
	e->users[sock]->ig = 0;
	e->users[sock]->type = FD_FREE;
	printf("Client disconnected : %d\n", sock);
}

void	check_actions(t_env *e, int cs)
{
	t_actions	*acts;
	double		now;
	int			*nb_acts;

	if (less_hp(e, cs) != -1)
	{
		nb_acts = &e->users[cs]->player.cur_aread;
		acts = &e->users[cs]->player.acts[*nb_acts];
		now = ft_usec_time();
		if (acts->time != 0 && acts->time <= now)
		{
			e->users[cs]->player.acts[*nb_acts].fct_cmd(e, cs);
			if (e->users[cs]->player.acts[*nb_acts].cmd != NULL)
			{
				free(e->users[cs]->player.acts[*nb_acts].cmd);
				e->users[cs]->player.acts[*nb_acts].cmd = NULL;
			}
			*nb_acts = (*nb_acts + 1) % 10;
			acts->time = 0;
		}
		else if (acts->start != 0 && acts->start <= now)
		{
			if (e->users[cs]->player.acts[*nb_acts].fct_gfx)
				e->users[cs]->player.acts[*nb_acts].fct_gfx(e, cs);
			acts->start = 0;
		}
	}
}

void	init_fd(t_env *e)
{
	int		i;

	i = 0;
	FD_ZERO(&e->srv.fd_read);
	FD_ZERO(&e->srv.fd_write);
	e->srv.max = 3;
	while (i < (e->srv.max_fd))
	{
		if (e->users[i]->type != FD_FREE)
		{
			if (e->users[i]->type == FD_CLT && e->users[i]->ig == 1
				&& !e->users[i]->gfx.gfx)
				check_actions(e, i);
			FD_SET(i, &e->srv.fd_read);
			if (verify_bsn(&e->users[i]->buf_write) == 1)
				FD_SET(i, &e->srv.fd_write);
			if (e->srv.max < i)
				e->srv.max = i;
		}
		i++;
	}
}

void	check_fd(t_env *e)
{
	int		i;

	i = 0;
	while (i < e->srv.max_fd && e->srv.r > 0)
	{
		if (e->users[i]->type != FD_FREE)
		{
			if (FD_ISSET(i, &e->srv.fd_write) != 0)
				e->users[i]->fct_write(e, i);
			else if (FD_ISSET(i, &e->srv.fd_read) != 0)
				e->users[i]->fct_read(e, i);
			if (FD_ISSET(i, &e->srv.fd_read) != 0 ||
				FD_ISSET(i, &e->srv.fd_write) != 0)
				e->srv.r--;
			if (e->users[i]->type == FD_CLT && e->users[i]->ig == 1
				&& !e->users[i]->gfx.gfx)
				verify_win(e, i);
		}
		i++;
	}
}
