/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 12:09:51 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/25 01:06:38 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		create_clt(char *addr, int port)
{
	int					s;
	struct protoent		*prt;
	struct sockaddr_in	c;

	c.sin_family = AF_INET;
	c.sin_port = htons(port);
	c.sin_addr.s_addr = inet_addr(addr);
	prt = (struct protoent*)XV(NULL, getprotobyname("tcp"), "getprotobyname");
	s = X(-1, socket(PF_INET, SOCK_STREAM, prt->p_proto), "socket");
	X(-1, connect(s, (const struct sockaddr *)&c, sizeof(c)), "connect");
	return (s);
}

void	check_fd(t_env *e)
{
	while (e->r != 0)
	{
		if (FD_ISSET(e->user->sock, &e->fd_read))
		{
			e->r--;
			rcv_serveur(e);
		}
		else if (FD_ISSET(e->user->sock, &e->fd_write))
		{
			e->r--;
			send_serveur(e);
		}
	}
}

void	do_select(t_env *e, struct timeval *out)
{
	fd_set				*read;
	fd_set				*write;
	int					aw;
	int					ar;

	aw = e->user->player.cur_awrite;
	ar = e->user->player.cur_aread;
	read = &e->fd_read;
	write = &e->fd_write;
	FD_SET(e->user->sock, read);
	if (verify_bsn(&e->user->buf_write) == 1)
		FD_SET(e->user->sock, write);
	if (e->user->player.acts[aw].time == 0
		&& e->user->player.acts[ar].wait == 0)
		e->r = select(e->user->sock + 1, read, write, NULL, out);
	else
		e->r = select(e->user->sock + 1, read, write, NULL, NULL);
}

void	run_clt(t_env *e)
{
	int					i;
	struct timeval		out;

	out.tv_usec = 0;
	out.tv_sec = 0;
	i = 1;
	init_clt(e);
	if ((e->user->sock = create_clt(e->me.host, e->me.port)) != -1)
	{
		while (i != 0)
		{
			FD_ZERO(&e->fd_read);
			FD_ZERO(&e->fd_write);
			do_select(e, &out);
			check_fd(e);
			try_ia(e);
			if (my_exit(1, NULL) == 1)
				i = 0;
		}
	}
}

int		main(int ac, char **av)
{
	t_env	e;

	if (get_clt_opt(&e.me, ac, av))
		return(1);
	e.av = av;
	run_clt(&e);
	return (0);
}
