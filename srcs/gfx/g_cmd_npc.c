/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_cmd_npc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 16:36:16 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/26 17:01:27 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

void		cmd_pie(char *cmd)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	i += get_next_int(&y, &cmd[i]);
	i += get_next_int(&x, &cmd[i]);
	printf("pie: %d %d\n", x, y);
	repel_incant(x, y);
}

void		cmd_plv(char *cmd)
{
	int		i;
	int		npc;

	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	i += get_next_int(&npc, &cmd[i]);
	if (npc >= NPCS_MAX || !g_env->npc[npc].id)
		return ;
	i += get_next_int(&g_env->npc[npc].lvl, &cmd[i]);
	printf("cmd_plv: %d %d\n", npc, g_env->npc[npc].lvl);
}

void		cmd_pdi(char *cmd)
{
	int		i;
	int		npc;

	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	i += get_next_int(&npc, &cmd[i]);
	if (npc >= NPCS_MAX || !g_env->npc[npc].id)
		return ;
	kill_mob(npc);
	if (g_env->npc[npc].team)
		free(g_env->npc[npc].team);
	bzero(&g_env->npc[npc], sizeof(t_npc));
	printf("cmd_pdi: %d\n", npc);
}
