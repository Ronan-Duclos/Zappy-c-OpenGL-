/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_cmd_pnw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 16:27:15 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/26 16:27:18 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

void		del_egg(void *ct)
{
	t_egg	*egg;

	egg = (t_egg *)ct;
	free(egg->team);
	free(egg);
}

static void	pnw_on_egg(t_npc *npc)
{
	t_list	**tmp;

	tmp = &g_env->egg;
	while (*tmp && strcmp(((t_egg *)(*tmp)->content)->team, npc->team))
		tmp = &(*tmp)->next;
	if (!*tmp)
		return ;
	del_link(&(*tmp), NULL);
	tmp = &g_env->sq[npc->x + g_env->mapw * npc->y].egg;
	while (*tmp && strcmp(((t_egg *)((*tmp)->content))->team, npc->team))
		tmp = &(*tmp)->next;
	if (!(*tmp))
		return ;
	del_link(&(*tmp), del_egg);
}

void		cmd_pnw(char *cmd)
{
	int		i;
	int		tmp;
	t_npc	*npc;

	printf("cmd_pnw: %s\n", cmd);
	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	i += get_next_int(&tmp, &cmd[i]);
	if (tmp >= NPCS_MAX || g_env->npc[tmp].id)
		return ;
	g_env->npc[tmp].id = tmp;
	i += get_next_int(&g_env->npc[tmp].y, &cmd[i]);
	i += get_next_int(&g_env->npc[tmp].x, &cmd[i]);
	i += get_next_int(&g_env->npc[tmp].dir, &cmd[i]);
	i += get_next_int(&g_env->npc[tmp].lvl, &cmd[i]);
	i++;
	g_env->npc[tmp].team = strdup(&cmd[i]);
	npc = &g_env->npc[tmp];
	pnw_on_egg(npc);
	add_mob(tmp, g_env->npc[tmp].x, g_env->npc[tmp].y, g_env->npc[tmp].dir);
}
