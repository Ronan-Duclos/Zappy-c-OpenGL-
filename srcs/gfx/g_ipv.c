/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_ipv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 16:12:50 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/17 15:45:20 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <strings.h>
#include "gfx.h"

void		get_opt(t_ipv *ipv, int ac, char **av)
{
	if (ac != 3)
	{
		fprintf(stderr, "Usage: %s <addr> <port>\nAnd Fuck You\n", av[0]);
		exit(1);
	}
	ipv->port = atoi(av[2]);
	if (ipv->port <= 0 || ipv->port > 99999)
	{
		fprintf(stderr, "%s: invalid port argument\n", av[0]);
		exit(1);
	}
}

void		ipv_init(t_ipv *ipv, int ac, char **av)
{
	bzero(ipv, sizeof(t_ipv));
	get_opt(ipv, ac, av);
	init_bc(&ipv->fd.buf_read);
	init_bc(&ipv->fd.buf_write);
	ipv->state = _connect;
}

void		*ipv_loop(void *args)
{
	t_ipv	*i;

	i = (t_ipv *)args;
	while (42)
	{
		fds_init(i);
		i->r = select(i->sock + 1, &i->fd_read, &i->fd_write, NULL, NULL);
		fds_check(i);
	}
	return (NULL);
}

