/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_cmd_egg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 18:46:27 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/26 17:00:54 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

void		cmd_enw(char *cmd)
{
	t_egg	*new;
	int		npc;
	int		i;
	int		x;
	int		y;

	printf("cmd_enw: %s\n", cmd);
	new = (t_egg *)XV(NULL, malloc(sizeof(t_egg)), "cmd_enw");
	bzero(new, sizeof(t_egg));
	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	i += get_next_int(&new->id, &cmd[i]);
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	i += get_next_int(&npc, &cmd[i]);
	i += get_next_int(&y, &cmd[i]);
	i += get_next_int(&x, &cmd[i]);
	new->x = x;
	new->y = y;
	new->team = strdup(g_env->npc[npc].team);
	add_link_end(&g_env->egg, new);
	add_link_end(&g_env->sq[x + g_env->mapw * y].egg, new);
}

void		cmd_ebo(char *cmd)
{
	t_list	*tmp;
	t_egg	*egg;
	int		i;
	int		id;

	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	get_next_int(&id, &cmd[i]);
	tmp = g_env->egg;
	while (tmp && ((t_egg *)(tmp->content))->id != id)
		tmp = tmp->next;
	if (!tmp)
		return ;
	egg = tmp->content;
	printf("cmd_ebo: egg: id %d, %d %d\n", egg->id, egg->x, egg->y);
}

void		cmd_eht(char *cmd)
{
	t_list	*tmp;
	t_egg	*egg;
	int		i;
	int		id;

	printf("cmd_eht: %s\n", cmd);
	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	get_next_int(&id, &cmd[i]);
	tmp = g_env->egg;
	while (tmp && ((t_egg *)(tmp->content))->id != id)
		tmp = tmp->next;
	if (!tmp)
		return ;
	egg = tmp->content;
	printf("cmd_eht: egg: id %d, %d %d\n", egg->id, egg->x, egg->y);
}

static int	edi_egg_get(t_list **egg, int id)
{
	t_list	**tmp;

	tmp = egg;
	while (*tmp && ((t_egg *)((*tmp)->content))->id != id)
		tmp = &(*tmp)->next;
	if (!*tmp)
		return (0);
	return (1);
}

void		cmd_edi(char *cmd)
{
	t_list	**tmp;
	t_egg	*egg;
	int		i;
	int		id;

	printf("cmd_edi: %s\n", cmd);
	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	get_next_int(&id, &cmd[i]);
	tmp = &g_env->egg;
	while (*tmp && ((t_egg *)((*tmp)->content))->id != id)
		*tmp = (*tmp)->next;
	if (!*tmp)
		return ;
	egg = (*tmp)->content;
	if (!edi_egg_get(&g_env->egg, id))
		return ;
	del_link(&(*tmp), NULL);
	if (!edi_egg_get(&g_env->sq[egg->x + g_env->mapw * egg->y].egg, id))
		return ;
	del_link(&(*tmp), del_egg);
}
