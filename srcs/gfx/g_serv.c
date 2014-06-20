/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_serv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 16:24:35 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/20 12:14:45 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "gfx.h"
#include "libft.h"

void		dtab_del(char **tab)
{
	int		i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		ft_strdel(&tab[i]);
		i++;
	}
	free(tab);
}

void		dtab_put(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		printf("%d: %s\n", i + 1, tab[i]);
		i++;
	}
}

void		srv_read(t_ipv *ipv)
{
	char	buf[BC_SIZE];
	int		r;

	bzero(buf, BC_SIZE);
	X(-1, (r = recv(ipv->sock, buf, BC_SIZE - 1, 0)), "srv_read");
	buf[r] = '\0';
	if (!r)
		exit(0);
	printf("\033[33mbuf: %s\n\033[0m", buf);
//	tmp_to_bc(&ipv->fd.buf_read, buf, 0);
//	if (verify_bsn(&ipv->fd.buf_read) == 1)
//	{
//		bzero(buf, BC_SIZE);
//		bc_to_tmp(&ipv->fd.buf_read, buf);
		cmd_check(ipv, buf);
		printf("after cmd_check\n");
//	}
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

