/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_serv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 16:24:35 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/11 19:01:26 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "gfx.h"
#include "libft.h"

void		srv_read(t_ipv *ipv)
{
	char	buf[BUF_SIZE];
	int		r;
	char	**tab;

	X(-1, (r = recv(ipv->sock, buf, BUF_SIZE - 1, 0)), "srv_read");
	buf[r] = '\0';
	if (!r)
		exit(0);
	printf("SRV send: [%s]\n", buf);
	tmp_to_bc(&ipv->fd.buf_read, buf, 0);
	if (verify_bsn(&ipv->fd.buf_read) == 1)
	{
		bzero(buf, BUF_SIZE);
		bc_to_tmp(&ipv->fd.buf_read, buf);
		if (!ipv->connected)
			cmd_connect(ipv, buf);
		tab = ft_strsplit(buf, '\n');
		dtab_put(tab);
	}
}

void		srv_write(t_ipv *ipv)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	bc_to_tmp(&ipv->fd.buf_write, buf);
	printf("send: [%s]\n", buf);
	send(ipv->sock, buf, strlen(buf), 0);
}

void		srv_connect(t_ipv *ipv, char **av)
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

