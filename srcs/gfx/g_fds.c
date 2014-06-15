/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_fds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 16:30:03 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/14 16:31:04 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/select.h>
#include "gfx.h"

#include <stdio.h>
#include <libft.h>

void		fds_init(t_ipv *ipv)
{
	FD_ZERO(&ipv->fd_read);
	FD_ZERO(&ipv->fd_write);
	FD_SET(ipv->sock, &ipv->fd_read);
	if (verify_bsn(&ipv->fd.buf_write) == 1)
		FD_SET(ipv->sock, &ipv->fd_write);
}

void		fds_check(t_ipv *ipv)
{
	printf("BEFORE FDS_CHECK, ipv: %p\n", ipv);
	if (FD_ISSET(ipv->sock, &ipv->fd_read))
	{
		printf("AFTER FD_ISSET, ipv: %p\n", ipv);
		srv_read(ipv);
		printf("AFTER SRV_READ %p\n", ipv);
	}
	else if (FD_ISSET(ipv->sock, &ipv->fd_write))
	{
		srv_write(ipv);
		printf("WRITE\n");
	}
	printf("coucou\n");
	printf("AFTER FDS_CHECK, ipv: %p\n", ipv);
}
