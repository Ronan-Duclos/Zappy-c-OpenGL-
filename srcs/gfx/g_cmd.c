/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 12:05:30 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/14 14:15:29 by caupetit         ###   ########.fr       */
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
	printf("in cmd_size: %s\n", &cmd[i]);
	i += get_next_int(&g_env->mapw, &cmd[i]);
	printf("in cmd_size: I:%d %s\n", i, &cmd[i]);
	i += get_next_int(&g_env->maph, &cmd[i]);
	printf("in cmd_size: X: %d, Y:%d\n", g_env->mapw, g_env->maph);
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

void		cmd_check(t_ipv *ipv, char *buf)
{
		char	**tab;

		tab = ft_strsplit(buf, '\n');
		if (ipv->state == _connect)
			cmd_connect(ipv, tab);
//		if (ipv_state == _sizes)
//			i += cmd_size(ipv, &tab[i]);
		dtab_put(tab);
		printf("in cmd_check: ipv->state: %d\n", ipv->state);
		dtab_del(tab);
}
