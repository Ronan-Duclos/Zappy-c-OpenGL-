/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_display_players.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 18:12:27 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/21 02:29:06 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

static void	display_mob(t_mob *mob)
{
	glPushMatrix();
	anim_move(mob->move);
	mob->anim->fct(mob->anim);
	glCallList(g_env->lists[_red]);
	glCallList(g_env->lists[_init_owl_pos]);
	glDrawElements(GL_TRIANGLES, g_env->vbosizes[_mod_owl][_vbo_indx], GL_UNSIGNED_SHORT, 0);
	glPopMatrix();
}

void		display_all_mobs(void)
{
	t_list	*list;
	int		i;

	i = 0;
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_owl][_vbo_vrtx]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_owl][_vbo_nrms]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_env->vbos[_mod_owl][_vbo_indx]);
	while (i < g_env->mapw * g_env->maph)
	{
		list = g_env->sq[i].mobs;
		while (list)
		{
			display_mob(list->content);
			list = list->next;
		}
		i++;
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
