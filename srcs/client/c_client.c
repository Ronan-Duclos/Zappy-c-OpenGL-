/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_client.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/17 18:11:48 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/07 22:24:31 by rduclos          ###   ########.fr       */
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

void	check_actions(t_env *e)
{
	while (e->r != 0)
	{
		if (FD_ISSET(0, &e->fd_read))
		{
			e->r--;
			rcv_keyboard(e);
		}
		else if (FD_ISSET(e->user->sock, &e->fd_write))
		{
			e->r--;
			send_serveur(e);
		}
		else if (FD_ISSET(e->user->sock, &e->fd_read))
		{
			e->r--;
			rcv_serveur(e);
		}
	}
}

void	do_select(t_env *e)
{
	fd_set	*read;
	fd_set	*write;

	read = &e->fd_read;
	write = &e->fd_write;
	FD_SET(0, read);
	FD_SET(e->user->sock, read);
	if (verify_bsn(&e->user->buf_write) == 1)
		FD_SET(e->user->sock, write);
	e->r = select(e->user->sock + 1, read, write, NULL, NULL);
}

void	run_clt(t_env *e)
{
	init_clt(e);
	if ((e->user->sock = create_clt(e->me.host, e->me.port)) != -1)
	{
		while (my_exit(1, NULL) != 1)
		{
			FD_ZERO(&e->fd_read);
			FD_ZERO(&e->fd_write);
			do_select(e);
			check_actions(e);
		}
		close(e->user->sock);
	}
}

int		main(int ac, char **av)
{
	t_env	e;

	if (get_clt_opt(&e.me, ac, av))
		return(1);
	run_clt(&e);
	return (0);
}
