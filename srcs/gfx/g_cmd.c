/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 12:05:30 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/24 15:30:14 by caupetit         ###   ########.fr       */
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

void		cmd_seg(char *cmd)
{
	int		i;

	printf("cmd_seg: %s\n", cmd);
	i = 0;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	// nom de team a dup et afficher: strdup(&cmd[i])
}

void		cmd_bct(char *cmd)
{
	int		i;
	int		x;
	int		y;
	int		*tab;

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
	printf("%s\n", cmd);
}

void		del_egg(void *ct)
{
	t_egg	*egg;

	egg = (t_egg *)ct;
	free(egg->team);
	free(egg);
}
/*
static void	pnw_on_egg(t_npc *npc)
{
	t_list	*tmp;

	tmp = g_env->egg;
	printf("here\n");
	while (tmp && strcmp(((t_egg *)tmp->content)->team, npc->team))
	{
		printf("egg team: %s\n", ((t_egg *)tmp->content)->team);
		tmp = tmp->next;
		printf("egg team: %s\n", ((t_egg *)tmp->content)->team);
	}
	if (!tmp)
		return ;
	del_link(&tmp, del_egg);
	printf("here2\n");
	tmp = g_env->sq[npc->x + g_env->mapw * npc->y].egg;
	while (tmp && strcmp(((t_egg *)(tmp->content))->team, npc->team))
		tmp = tmp->next;
	if (!tmp)
		return ;
	del_link(&tmp, del_egg);
}
*/
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
	npc = &g_env->npc[tmp];
	npc[tmp].id = tmp;
	i += get_next_int(&npc->y, &cmd[i]);
	i += get_next_int(&npc->x, &cmd[i]);
	i += get_next_int(&npc->dir, &cmd[i]);
	i += get_next_int(&npc->lvl, &cmd[i]);
	i++;
	npc->team = strdup(&cmd[i]);
//	pnw_on_egg(npc);
	add_mob(tmp, npc->x, npc->y, npc->dir);
/*
	g_env->npc[tmp].id = tmp;
	i += get_next_int(&g_env->npc[tmp].y, &cmd[i]);
	i += get_next_int(&g_env->npc[tmp].x, &cmd[i]);
	i += get_next_int(&g_env->npc[tmp].dir, &cmd[i]);
	i += get_next_int(&g_env->npc[tmp].lvl, &cmd[i]);
	i++;
	// if oeuf de la team sur la case
	// supprimer oeuf
	g_env->npc[tmp].team = strdup(&cmd[i]);
	add_mob(tmp, g_env->npc[tmp].x, g_env->npc[tmp].y, g_env->npc[tmp].dir);
*/
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
	i += get_next_int(&g_env->npc[npc].y, &cmd[i]);
	i += get_next_int(&g_env->npc[npc].x, &cmd[i]);
	i += get_next_int(&g_env->npc[npc].dir, &cmd[i]);
	printf("cmd_ppo: %d, %d %d, %d", npc,
		   g_env->npc[npc].x,
		   g_env->npc[npc].y,
		   g_env->npc[npc].dir);//
	move_mob(npc, g_env->npc[npc].x, g_env->npc[npc].y, g_env->npc[npc].dir);
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
	i += get_next_int(&g_env->npc[npc].y, &cmd[i]);
	i += get_next_int(&g_env->npc[npc].x, &cmd[i]);
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

void		cmd_pie(char *cmd)
{
	printf("cmd_pin: %s\n", cmd);//
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
	lower_mob(npc);
	printf("cmd_pgt: %d %d\n", npc, itm);
}

void		cmd_pdr(char *cmd)
{
	int		i;
	int		npc;
	int		itm;

	printf("cmd_pdr: %s\n", cmd);
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

void		cmd_pdi(char *cmd)
{
	int		i;
	int		npc;

	printf("cmd_pdi: %s\n", cmd);
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
	// ici npc == id jour qui fork
	printf("cmd_pfk: %d\n", npc);
}

void		cmd_pic(char *cmd)
{
	int		i;
	int		pos[2];
	int		npc;
	int		lvl;

	printf("cmd_pic: %s\n", cmd);
	i = 0;
	i += get_next_int(&pos[1], &cmd[i]);
	i += get_next_int(&pos[0], &cmd[i]);
	i += get_next_int(&lvl, &cmd[i]);
		// lancer ici l'anim incant de la case (pierres)
		// lvl    == niveau de l'icantation
		// pos[0] == x de la case ou lancer l'incant
		// pos[1] == y de la case...
	while (cmd[i])
	{
		while (cmd[i] == ' ' || cmd[i] == '#')
			i++;
		i += get_next_int(&npc, &cmd[i]);
		if (npc >= NPCS_MAX || !g_env->npc[npc].id)
			return ;
		// npc    == id joueur qui dois lancer l'anim incant
	}
}

void		cmd_enw(char *cmd)
{
	t_egg	*new;
	int		i;
	int		npc;
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
	printf("pnw: name env: %s\n", ((t_egg *)g_env->egg->content)->team);
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
	// ici l'oeuf 'egg' eclos, deal with it !
	// surement innutile cette commande
	printf("cmd_eht: egg: id %d, %d %d\n", egg->id, egg->x, egg->y);
}

void		cmd_ebo(char *cmd)
{
	t_list	*tmp;
	t_egg	*egg;
	int		i;
	int		id;

	printf("cmd_ebo: %s\n", cmd);
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
	// ici l'oeuf un joueur ce connecte pour l'oeuf, deal with it !
	// surement innutile cette commande
	printf("cmd_ebo: egg: id %d, %d %d\n", egg->id, egg->x, egg->y);
}
