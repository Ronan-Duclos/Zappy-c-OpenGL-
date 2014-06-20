/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_npc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 19:32:54 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/20 01:14:47 by tmielcza         ###   ########.fr       */
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
