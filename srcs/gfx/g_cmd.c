/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 12:05:30 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/26 18:52:09 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"
#include "gfx.h"
#include "libft.h"

void		cmd_bct(char *cmd)
{
	int		i;
	int		x;
	int		y;
	int		*tab;

	printf("cmd_bct: %s\n", cmd);
	i = 0;
	i += get_next_int(&y, &cmd[i]);
	i += get_next_int(&x, &cmd[i]);
	tab = g_env->sq[x + g_env->mapw * y].itms;
	i += get_next_int(&tab[0], &cmd[i]);
	i += get_next_int(&tab[1], &cmd[i]);
	i += get_next_int(&tab[2], &cmd[i]);
	i += get_next_int(&tab[3], &cmd[i]);
	i += get_next_int(&tab[4], &cmd[i]);
	i += get_next_int(&tab[5], &cmd[i]);
	i += get_next_int(&tab[6], &cmd[i]);
}

void		cmd_pfk(char *cmd)
{
	int		i;
	int		npc;

	printf("cmd_pfk: %s\n", cmd);
	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	i += get_next_int(&npc, &cmd[i]);
	if (npc >= NPCS_MAX || !g_env->npc[npc].id)
		return ;
	printf("cmd_pfk: %d\n", npc);
}

void		cmd_pic(char *cmd)
{
	int		i;
	int		pos[2];
	int		npc;
	int		lvl;

	i = 0;
	i += get_next_int(&pos[1], &cmd[i]);
	i += get_next_int(&pos[0], &cmd[i]);
	i += get_next_int(&lvl, &cmd[i]);
	printf("cmd_pic %d %d\n", pos[0], pos[1]);
	cast_incant(pos[0], pos[1]);
	while (cmd[i])
	{
		while (cmd[i] == ' ' || cmd[i] == '#')
			i++;
		i += get_next_int(&npc, &cmd[i]);
		if (npc >= NPCS_MAX || !g_env->npc[npc].id)
			return ;
	}
}

void		cmd_pcb(char *cmd)
{
	char	buf[BUF_SIZE];
	int		i;
	int		npc;

	bzero(buf, BUF_SIZE);
	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	i += get_next_int(&npc, &cmd[i]);
	while (cmd[i] && cmd[i] == ' ')
		i++;
	strcpy(buf, &cmd[i]);
	broadcast(npc);
	printf("cmd_pcb: %d [%s]\n", npc, buf);
}
