/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_incant_action.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 03:10:20 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/26 15:29:41 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

void	cast_incant(int x, int y)
{
	t_square	*sq;
	t_item		*item;
	t_anim		*anim;
	int			i;
	int			time;

	time = T_SPELL * FPS / g_env->time;
	sq = &g_env->sq[x + y * g_env->mapw];
	i = 0;
	while (i < 4)
	{
		anim = new_anim(0, time, anim_incant);
		item = new_item(0, _mod_totem, anim, &display_totem);
		sq->anims = new_link(sq->anims, item);
		i++;
	}
}

void	repel_incant(int x, int y)
{
	t_list	**list;
	int		i;

	i = 0;
	while (i < 4)
	{
		list = &g_env->sq[x + y * g_env->mapw].anims;
		while (*list && ((t_item *)(*list)->content)->fct != display_totem)
			list = &(*list)->next;
		if (*list)
			del_link(list, NULL);
		i++;
	}
}
