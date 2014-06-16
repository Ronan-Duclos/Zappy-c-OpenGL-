/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 12:05:30 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/16 18:00:21 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"
#include "gfx.h"
#include "libft.h"

int			get_next_int(int *nb, char *s)
{
	int		i;
	int		tmp;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	*nb = ft_atoi(&s[i]);
	tmp = *nb;
	i++;
	while (tmp / 10)
	{
		tmp /= 10;
		i++;
	}
	return (i);
}

void		cmd_msz(char *cmd)
{
	int		i;

	i = 3;
	i += get_next_int(&g_env->mapw, &cmd[i]);
	i += get_next_int(&g_env->maph, &cmd[i]);
	if (!g_env->sq)
		map_init();
}

void		cmd_sgt(char *cmd)
{
	int		i;

	i = 3;
	get_next_int(&g_env->time, &cmd[i]);
}

void		cmd_bct(char *cmd)
{
	int		i;
	int		x;
	int		y;
	int		*tab;

	i = 3;
	i += get_next_int(&x, &cmd[i]);
	i += get_next_int(&y, &cmd[i]);
	tab = g_env->sq[x + g_env->mapw * y].itms;
	i += get_next_int(&tab[0], &cmd[i]);
	i += get_next_int(&tab[1], &cmd[i]);
	i += get_next_int(&tab[2], &cmd[i]);
	i += get_next_int(&tab[3], &cmd[i]);
	i += get_next_int(&tab[4], &cmd[i]);
	i += get_next_int(&tab[5], &cmd[i]);
	i += get_next_int(&tab[6], &cmd[i]);
}

#include "libft.h" ////
#include <string.h> ///

static void	cmds_get(char ***tab, char *buf)
{
	static char	tmp[BUF_SIZE];
	char		tmp2[BUF_SIZE];
	char		*tmp3;

	bzero(tmp2, BUF_SIZE);
	if (*tmp)
		strcpy(tmp2, tmp);
	bzero(tmp, BUF_SIZE);
	if (buf[strlen(buf) - 1] != '\n' && (tmp3 = strrchr(buf, '\n')))
	{
		strcpy(tmp, tmp3 + 1);
		tmp3 = '\0';
	}
	*tab = ft_strsplit(buf, '\n');
	if (*tmp2)
	{
		strcpy(&tmp2[strlen(tmp2)], *tab[0]);
		tmp3 = strdup(tmp2);
		free(*tab[0]);
		*tab[0] = tmp3;
	}
}

void		cmd_check(t_ipv *ipv, char *buf)
{
		char		**tab;

		cmds_get(&tab, buf);
		if (ipv->state == _connect)
			cmd_connect(ipv, tab);
		dtab_del(tab);
}
