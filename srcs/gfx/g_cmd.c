/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 12:05:30 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/18 17:44:52 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"
#include "gfx.h"
#include "libft.h"

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

void		cmd_pnw(char *cmd)
{
	int		i;
	int		tmp;

	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	i += get_next_int(&tmp, &cmd[i]);
	if (tmp >= NPCS_MAX)
		return ;
	i += get_next_int(&g_env->npc[tmp].x, &cmd[i]);
	i += get_next_int(&g_env->npc[tmp].y, &cmd[i]);
	i += get_next_int(&g_env->npc[tmp].dir, &cmd[i]);
	i += get_next_int(&g_env->npc[tmp].lvl, &cmd[i]);
	i++;
	g_env->npc[tmp].team = strdup(&cmd[i]);
}
