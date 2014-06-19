/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_cmd_send.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 12:08:47 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/19 17:22:12 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

void		cmd_pin_send(t_ipv *ipv, int clt)
{
	char	buf[BUF_SIZE];

	printf("cmd_pin_send\n");
	bzero(buf, BUF_SIZE);
	sprintf(buf, "pin #%d", clt);
	tmp_to_bc(&ipv->fd.buf_write, buf, 1);
}

void		cmd_plv_send(t_ipv *ipv, int clt)
{
	char	buf[BUF_SIZE];

	printf("cmd_plv_send\n");
	bzero(buf, BUF_SIZE);
	sprintf(buf, "plv #%d", clt);
	tmp_to_bc(&ipv->fd.buf_write, buf, 1);
}
