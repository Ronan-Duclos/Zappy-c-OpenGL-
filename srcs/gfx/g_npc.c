/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_npc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 19:32:54 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/24 00:48:26 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

/*
**	Finds a mob npc and returns a pointer on the pointer pointing on his link.
*/
t_list	**find_mob(int npc)
{
	t_npc	*n;
	t_list	**tmp;

	n = g_env->npc + npc;
	tmp = &n->sq->mobs;
	while (((t_mob *)(*tmp)->content)->id != npc)
		tmp = &(*tmp)->next;
	return (tmp);
}

int			is_in_list(t_list *link, t_list *list)
{
	while (list)
	{
		if (list == link)
			return (1);
		list = list->next;
	}
	return (0);
}

t_mob		*new_mob(t_anim *anim, t_move *move, t_rot *rot, int id)
{
	t_mob	*new;

	new = (t_mob *)XV(NULL, malloc(sizeof(t_mob)), "malloc");
	new->move = move;
	new->rot = rot;
	new->anim = anim;
	new->id = id;
	return (new);
}

void		del_mob(void *ptr)
{
	t_mob	*mob;

	mob = (t_mob *)ptr;
	if (mob->anim)
		free(mob->anim);
	if (mob->move)
		free(mob->move);
	if (mob->rot)
		free(mob->rot);
	free(mob);
}
