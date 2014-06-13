/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_connect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 13:44:17 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/13 18:10:09 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "gfx.h"
#include "gfx_gl.h"

static void	connect_error(int sock, char *func, int step)
{
	fprintf(stderr, "Serveur fucked us: %s, step %d\n", func, step);
	X(-1, close(sock), "close");
	exit(0);
}

static int	connect_init(t_ipv *ipv, char **tab)
{
	if (strcmp(tab[0], "BIENVENUE"))
		connect_error(ipv->sock, "connect_init", 0);
	tmp_to_bc(&ipv->fd.buf_write, "GRAPHIC", 1);
	return (1);
}

static int	connect_sizes(t_ipv *ipv, char **tab, int *i)
{
	static int	step;

	if (!step && strncmp(tab[*i], "msz", 3))
		connect_error(ipv->sock, "connect_sizes", step);
	else if (!step && tab[*i])
	{
		cmd_msz(tab[*i]);
		*i += 1;
		step += 1;
	}
	if (step == 1 && tab[*i] && !strncmp(tab[*i], "sgt", 3))
	{
		cmd_sgt(tab[*i]);
		*i += 1;
		step += 1;	
	}
	if (step == 2)
	{
		step = 0;
		return (1);
	}
	return (0);
}

static int	connect_map(char **tab, int *i)
{
	static int	step;

	printf("I: %d\n", *i);
	while (tab[*i] && !strncmp(tab[*i], "bct", 3))
	{
		cmd_bct(tab[*i]);
		step += 1;
		*i += 1;
	}
	printf("total map: %d, step: %d\n", g_env->mapw * g_env->maph, step);
	if (step == g_env->mapw * g_env->maph - 2)
	{
		step = 0;
		return (1);
	}
	return (0);
}

void		cmd_connect(t_ipv *ipv, char **tab)
{
	static int	step;
	int			i;

	i = 0;
	if (!step)
		step += connect_init(ipv, &tab[i]);
	else if (step == 1)
		step += connect_sizes(ipv, &tab[i], &i);
	if (step == 2)
		step += connect_map(&tab[i], &i);
	printf("sizes: X: %d, Y: %d, Time: %d\n", g_env->mapw, g_env->maph, g_env->time);
	printf("step: %d\n", step);
}

