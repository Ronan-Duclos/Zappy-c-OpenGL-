/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 20:06:02 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/13 10:51:01 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "libft.h"

void	create_clt(t_env *e, int s)
{
	int						cs;
	unsigned int			len;
	struct sockaddr_in		clt;

//	len = sizeof(clt); // lin
	cs = X(-1, accept(s, (struct sockaddr *)&clt, &len), "accepte");
	e->users[cs]->type = FD_CLT;
	e->users[cs]->fct_read = client_read;
	e->users[cs]->fct_write = client_write;
	bzero(&e->users[cs]->player, sizeof(t_player));
	init_pos(e->users[cs], e->opt.x, e->opt.y);
	e->users[cs]->player.inv[_food] = 10;
	e->users[cs]->player.direc = rand_int(NORTH, WEST);
	tmp_to_bc(&e->users[cs]->buf_write, "BIENVENUE", 1);
	printf("Client connected : %d\n", cs);
}

void	destroy_clt(t_env *e, int sock)
{
	e->users[sock]->type = FD_FREE;
	if (e->users[sock]->player.team != NULL)
		free(e->users[sock]->player.team);
	e->users[sock]->player.team = NULL;
	init_bc(&e->users[sock]->buf_read);
	init_bc(&e->users[sock]->buf_write);
	e->users[sock]->buf_read_tmp[0] = '\0';
	e->users[sock]->buf_write_tmp[0] = '\0';
	e->users[sock]->ig = 0;
	if (e->users[sock]->gfx)
		glst_del_one(&e->srv.glst, sock);
	e->users[sock]->gfx = 0;
	printf("Client disconnected : %d\n", sock);
}

void	check_actions(t_env *e, int cs)
{
	t_actions	*acts;
	double		now;
	int			nb_acts;

	nb_acts = e->users[cs]->player.cur_aread;
	acts = &e->users[cs]->player.acts[nb_acts];
	now = ft_usec_time();
	if (acts->time != 0 && acts->time <= now)
	{
		e->users[cs]->player.acts[nb_acts].fct_cmd(e, cs);
		if (e->users[cs]->player.cur_aread == 9)
			e->users[cs]->player.cur_aread = 0;
		else
			e->users[cs]->player.cur_aread++;
		acts->time = 0;
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
			if (e->users[i]->type == FD_CLT && e->users[i]->ig == 1)
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
		}
		i++;
	}
}
