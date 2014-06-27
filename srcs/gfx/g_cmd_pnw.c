/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_cmd_pnw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 16:27:15 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/27 04:36:48 by tmielcza         ###   ########.fr       */
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

	printf("Coucou (begining)\n");
	tmp = &g_env->egg;
	printf("npc->team = %s\n", npc->team);
	printf("tmp = %p\n", *tmp);
	if (*tmp)
	{	printf("tmp->truc = %p\n", (*tmp)->content);
		printf("tmp->truc->truc = %d\n", ((t_egg *)(*tmp)->content)->id);
		printf("tmp->truc->truc = %s\n", ((t_egg *)(*tmp)->content)->team);}
	while (*tmp && strcmp(((t_egg *)(*tmp)->content)->team, npc->team))
	{
		printf("%p, %p\n", *tmp, (*tmp)->content);
		tmp = &(*tmp)->next;
	}
	printf("LOL\n");
	if (!*tmp)
		return ;
	del_link(&(*tmp), NULL);
	printf("Pouet\n");
	tmp = &g_env->sq[npc->x + g_env->mapw * npc->y].egg;
	while (*tmp && strcmp(((t_egg *)((*tmp)->content))->team, npc->team))
		tmp = &(*tmp)->next;
	printf("Hey\n");
	if (!(*tmp))
		return ;
	printf("\033[31mDEL\033[0m\n");
	del_link(&(*tmp), del_egg);
	printf("Enrevoir\n");
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
	if (!g_env->npc[tmp].lvl)
	{
		printf("Bad player recieved");
		bzero(&g_env->npc[tmp], sizeof(t_npc));
		return ;
	}
	g_env->npc[tmp].team = strdup(&cmd[i]);
	npc = &g_env->npc[tmp];
	pnw_on_egg(npc);
	add_mob(tmp, g_env->npc[tmp].x, g_env->npc[tmp].y, g_env->npc[tmp].dir);
}
