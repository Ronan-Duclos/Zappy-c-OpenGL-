/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 12:05:30 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/19 18:23:40 by caupetit         ###   ########.fr       */
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

	printf("cmd_pnw: %s\n", cmd);
	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	i += get_next_int(&tmp, &cmd[i]);
	if (tmp >= NPCS_MAX || g_env->npc[tmp].id)
		return ;
	g_env->npc[tmp].id = tmp;
	i += get_next_int(&g_env->npc[tmp].x, &cmd[i]);
	i += get_next_int(&g_env->npc[tmp].y, &cmd[i]);
	i += get_next_int(&g_env->npc[tmp].dir, &cmd[i]);
	i += get_next_int(&g_env->npc[tmp].lvl, &cmd[i]);
	i++;
	g_env->npc[tmp].team = strdup(&cmd[i]);
	printf("okayy\n");
}

void		cmd_ppo(char *cmd)
{
	int		i;
	int		npc;

	printf("cmd_ppo: %s\n", cmd);//
	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	i += get_next_int(&npc, &cmd[i]);
	if (npc >= NPCS_MAX || !g_env->npc[npc].id)
		return ;
	i += get_next_int(&g_env->npc[npc].x, &cmd[i]);
	i += get_next_int(&g_env->npc[npc].y, &cmd[i]);
	i += get_next_int(&g_env->npc[npc].dir, &cmd[i]);
	printf("cmd_ppo: %d, %d %d, %d", npc,
		   g_env->npc[npc].x,
		   g_env->npc[npc].y,
		   g_env->npc[npc].dir);//
}

void		cmd_pin(char *cmd)
{
	int		i;
	int		npc;

	printf("cmd_pin: %s\n", cmd);//
	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	i += get_next_int(&npc, &cmd[i]);
	if (npc >= NPCS_MAX || !g_env->npc[npc].id)
		return ;
	i += get_next_int(&g_env->npc[npc].x, &cmd[i]);
	i += get_next_int(&g_env->npc[npc].y, &cmd[i]);
	i += get_next_int(&g_env->npc[npc].inv[_food], &cmd[i]);
	i += get_next_int(&g_env->npc[npc].inv[_linemate], &cmd[i]);
	i += get_next_int(&g_env->npc[npc].inv[_deraumere], &cmd[i]);
	i += get_next_int(&g_env->npc[npc].inv[_sibur], &cmd[i]);
	i += get_next_int(&g_env->npc[npc].inv[_mendiane], &cmd[i]);
	i += get_next_int(&g_env->npc[npc].inv[_phiras], &cmd[i]);
	i += get_next_int(&g_env->npc[npc].inv[_thystame], &cmd[i]);
	printf("cmd_pin: %d, %d %d, %d, %d, %d, %d, %d, %d, %d, \n", npc,
		   g_env->npc[npc].x,
		   g_env->npc[npc].y,
		   g_env->npc[npc].inv[_food],
		   g_env->npc[npc].inv[_linemate],
		   g_env->npc[npc].inv[_deraumere],
		   g_env->npc[npc].inv[_sibur],
		   g_env->npc[npc].inv[_mendiane],
		   g_env->npc[npc].inv[_phiras],
		   g_env->npc[npc].inv[_thystame]);
}

void		cmd_plv(char *cmd)
{
	int		i;
	int		npc;

	printf("cmd_plv: %s\n", cmd);//
	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	i += get_next_int(&npc, &cmd[i]);
	if (npc >= NPCS_MAX || !g_env->npc[npc].id)
		return ;
	i += get_next_int(&g_env->npc[npc].x, &cmd[i]);
	printf("cmd_plv: %d %d\n", npc, g_env->npc[npc].lvl);
}

void		cmd_pgt(char *cmd)
{
	int		i;
	int		npc;
	int		itm;

	printf("cmd_pgt: %s\n", cmd);//
	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	i += get_next_int(&npc, &cmd[i]);
	if (npc >= NPCS_MAX || !g_env->npc[npc].id)
		return ;
	i += get_next_int(&itm, &cmd[i]);
	// ici npc == id jour qui prends, itm le type de pierre.
	printf("cmd_pgt: %d %d\n", npc, itm);
}
