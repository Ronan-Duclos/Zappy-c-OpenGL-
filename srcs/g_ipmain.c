/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_ipmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 11:25:03 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/11 13:41:31 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "common.h"
#include "gfx.h"

void		get_opt(t_ipv *ipv, int ac, char **av)
{
	if (ac != 3)
	{
		dprintf(2, "Usage: %s <addr> <port>\nAnd Fuck You\n", &av[0]);
		exit(1);
	}
	ipv->port = atoi(av[2]);
	if (ipv->port <= 0 || ipv->port > 99999)
	{
		dprintf(2, "%s: invalid port argument\n", av[0]);
		exit(1);
	}
}

void		connect_srv(t_ipv *ipv, char **av)
{
	struct protoent		*prt;
	struct sockaddr_in	c;

	c.sin_family = AF_INET;
	c.sin_port = htons(ipv->port);
	c.sin_addr.s_addr = inet_addr(av[1]);
	prt = (struct protoent *)XV(NULL, getprotobyname("tcp"), "getprotobyname");
	ipv->sock = X(-1, socket(PF_INET, SOCK_STREAM, prt->p_proto), "socket");
	X(-1, connect(ipv->sock, (struct sockaddr *)&c, sizeof(c)), "connect");
}

void		ipv_init(t_ipv *ipv, int ac, char **av)
{
	get_opt(ipv, ac, av);
	init_bc(&ipv->fd.buf_read);
	init_bc(&ipv->fd.buf_write);
	connect_srv(ipv, av);
}


int			main(int ac, char **av)
{
	t_ipv	ipv;

	ipv_init(&ipv, ac, av);
	
	printf("init_ok\n");
	return (0);
}
