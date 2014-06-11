/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_ipmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 11:25:03 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/11 18:56:12 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include "gfx.h"

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

void		cmd_connect(t_ipv *ipv, char *buf)
{
	if (strcmp(buf, "BIENVENUE\n"))
	{
		fprintf(stderr, "Serveur tried to fuck us\n");
		X(-1, close(ipv->sock), "close");
		exit(0);
	}
	tmp_to_bc(&ipv->fd.buf_write, "GRAPHIC", 1);
	ipv->connected = 1;
}

int			main(int ac, char **av)
{
	t_ipv	ipv;

	ipv_init(&ipv, ac, av);
	srv_connect(&ipv, av);
	ipv_loop(&ipv);
	return (0);
}
