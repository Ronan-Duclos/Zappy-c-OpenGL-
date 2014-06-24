/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_incant_action.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 03:10:20 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/24 20:04:13 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

void	cast_incant(int x, int y)
{
	t_square	*sq;
	t_item		*item;
	t_anim		*anim;
	int			i;

	sq = &g_env->sq[x + y * g_env->mapw];
	i = 0;
	while (i < 4)
	{
		anim = new_anim(0, 500, anim_incant);
		item = new_item(0, _mod_totem, anim, &display_totem);
		sq->anims = new_link(sq->anims, item);
		i++;
	}
}

void	repel_incant()
{}
