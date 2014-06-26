/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_cmd_npc_action.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 16:32:27 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/26 17:04:18 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

void		cmd_ppo(char *cmd)
{
	int		i;
	int		npc;

	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	i += get_next_int(&npc, &cmd[i]);
	if (npc >= NPCS_MAX || !g_env->npc[npc].id)
		return ;
	i += get_next_int(&g_env->npc[npc].y, &cmd[i]);
	i += get_next_int(&g_env->npc[npc].x, &cmd[i]);
	i += get_next_int(&g_env->npc[npc].dir, &cmd[i]);
	g_env->npc[npc].dir += 1;
	g_env->npc[npc].dir %= 4;
	printf("cmd_ppo: %d, %d %d, %d\n", npc,
		g_env->npc[npc].x,
		g_env->npc[npc].y,
		g_env->npc[npc].dir);
	move_mob(npc, g_env->npc[npc].x, g_env->npc[npc].y, g_env->npc[npc].dir);
}

void		cmd_pin(char *cmd)
{
	int		i;
	int		npc;
	int		j;

	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	i += get_next_int(&npc, &cmd[i]);
	if (npc >= NPCS_MAX || !g_env->npc[npc].id)
		return ;
	i += get_next_int(&j, &cmd[i]);
	i += get_next_int(&j, &cmd[i]);
	i += get_next_int(&g_env->npc[npc].inv[_food], &cmd[i]);
	i += get_next_int(&g_env->npc[npc].inv[_linemate], &cmd[i]);
	i += get_next_int(&g_env->npc[npc].inv[_deraumere], &cmd[i]);
	i += get_next_int(&g_env->npc[npc].inv[_sibur], &cmd[i]);
	i += get_next_int(&g_env->npc[npc].inv[_mendiane], &cmd[i]);
	i += get_next_int(&g_env->npc[npc].inv[_phiras], &cmd[i]);
	i += get_next_int(&g_env->npc[npc].inv[_thystame], &cmd[i]);
}

void		cmd_pgt(char *cmd)
{
	int		i;
	int		npc;
	int		itm;

	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	i += get_next_int(&npc, &cmd[i]);
	if (npc >= NPCS_MAX || !g_env->npc[npc].id)
		return ;
	i += get_next_int(&itm, &cmd[i]);
	lower_mob(npc);
	printf("cmd_pgt: %d %d\n", npc, itm);
}

void		cmd_pdr(char *cmd)
{
	int		i;
	int		npc;
	int		itm;

	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	i += get_next_int(&npc, &cmd[i]);
	if (npc >= NPCS_MAX || !g_env->npc[npc].id)
		return ;
	i += get_next_int(&itm, &cmd[i]);
	lower_mob(npc);
	printf("cmd_pdr: %d %d\n", npc, itm);
}
