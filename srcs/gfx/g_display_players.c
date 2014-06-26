/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_display_players.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 18:12:27 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/27 00:03:09 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

static void	team_color(int id)
{
	GLfloat	*col;
	char	*team;
	int		i;

	i = 0;
	team = g_env->npc[id].team;
	while (ft_strcmp(team, g_env->tnames[i]))
		i++;
	col = g_env->teamcol[i];
	glBlendColor(col[0], col[1], col[2], 0.0);
}

static void	display_geo(enum e_models mod)
{
	int		size;

	size = g_env->vbosizes[mod][_vbo_indx];
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[mod][_vbo_texp]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[mod][_vbo_vrtx]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[mod][_vbo_nrms]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_env->vbos[mod][_vbo_indx]);
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_SHORT, 0);
}

static void display_geos(void)
{
	glCallList(g_env->lists[_white]);
	display_geo(_mod_owl1);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_owl2][_vbo_texp]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_owl2][_vbo_vrtx]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_owl2][_vbo_nrms]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_env->vbos[_mod_owl2][_vbo_indx]);
	glBlendFunc(GL_CONSTANT_COLOR, GL_ZERO);
	glDrawElements(GL_TRIANGLES, g_env->vbosizes[_mod_owl2][_vbo_indx],
				GL_UNSIGNED_SHORT, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawElements(GL_TRIANGLES, g_env->vbosizes[_mod_owl2][_vbo_indx],
				GL_UNSIGNED_SHORT, 0);
	display_geo(_mod_owl3);
}

static void	display_mob(t_mob *mob)
{
	glPushMatrix();
	mob->move->fct(mob->move);
	mob->anim->fct(mob->anim);
	team_color(mob->id);
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

	i = -1;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_env->zepptex);
	while (++i < g_env->mapw * g_env->maph)
	{
		if (g_env->realpos0y[0] > i % g_env->mapw * 2.0 + 3.0
			|| g_env->realposxy[0] < i % g_env->mapw * 2.0 - 3.0
			|| g_env->realposxy[2] > i / g_env->mapw * 2.0 + 3.0
			|| g_env->realpos00[2] < i / g_env->mapw * 2.0 - 3.0)
			continue ;
		list = g_env->sq[i].mobs;
		while (list)
		{
			display_mob(list->content);
			list = list->next;
		}
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisable(GL_TEXTURE_2D);
}
