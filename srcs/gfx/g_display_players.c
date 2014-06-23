/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_display_players.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 18:12:27 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/23 19:34:37 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

void		display_geos(void)
{
	glCallList(g_env->lists[_white]);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_owl1][_vbo_texp]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_owl1][_vbo_vrtx]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_owl1][_vbo_nrms]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_env->vbos[_mod_owl1][_vbo_indx]);
	glDrawElements(GL_TRIANGLES, g_env->vbosizes[_mod_owl1][_vbo_indx], GL_UNSIGNED_SHORT, 0);

	glBlendColor(1.0, 0.0, 0.0, 1.0);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_owl2][_vbo_texp]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_owl2][_vbo_vrtx]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_owl2][_vbo_nrms]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_env->vbos[_mod_owl2][_vbo_indx]);
	glBlendFunc(GL_CONSTANT_COLOR, GL_ZERO);
	glDrawElements(GL_TRIANGLES, g_env->vbosizes[_mod_owl2][_vbo_indx], GL_UNSIGNED_SHORT, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawElements(GL_TRIANGLES, g_env->vbosizes[_mod_owl2][_vbo_indx], GL_UNSIGNED_SHORT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_owl3][_vbo_texp]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_owl3][_vbo_vrtx]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_owl3][_vbo_nrms]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_env->vbos[_mod_owl3][_vbo_indx]);
	glDrawElements(GL_TRIANGLES, g_env->vbosizes[_mod_owl3][_vbo_indx], GL_UNSIGNED_SHORT, 0);
}

static void	display_mob(t_mob *mob)
{
	glPushMatrix();
	mob->move->fct(mob->move);
	mob->anim->fct(mob->anim);
	glCallList(g_env->lists[_red]);
	glCallList(g_env->lists[_init_owl_pos]);
	anim_rot(mob->rot);
	display_geos();
	glPopMatrix();
}

void		display_all_mobs(void)
{
	t_list	*list;
	int		i;

	i = 0;
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glBindTexture(GL_TEXTURE_2D, g_env->zepptex);
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
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
}
