/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_display_items.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 22:26:42 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/27 07:40:45 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "gfx_gl.h"
#include "mdx.h"

void		display_egg(int i)
{
	glEnable(GL_TEXTURE_2D);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_egg][_vbo_texp]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_egg][_vbo_vrtx]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_egg][_vbo_nrms]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_env->vbos[_mod_egg][_vbo_indx]);
	glBindTexture(GL_TEXTURE_2D, g_env->textures[_tex_egg]);
	glPushMatrix();
	glCallList(g_env->lists[_white]);
	glTranslatef(1.9 / 16.0 * (i % 16) + 0.1, 0.0, 1.9 / 16 * (i / 16) + 0.1);
	glCallList(g_env->lists[_init_egg_pos]);
	glDrawElements(GL_TRIANGLES, g_env->vbosizes[_mod_egg][_vbo_indx],
				GL_UNSIGNED_SHORT, 0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void		display_totem(t_item *item)
{
	GLuint		*vbos;
	int			*sizes;
	static int	i = 0;

	vbos = g_env->vbos[item->vbo];
	sizes = g_env->vbosizes[item->vbo];
	glEnable(GL_TEXTURE_2D);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[_vbo_texp]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[_vbo_vrtx]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[_vbo_nrms]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[_vbo_indx]);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, g_env->textures[_tex_totem]);
	glCallList(g_env->lists[_white]);
	glTranslatef(1.6 * (i % 2) + 0.2, 0.0, 1.6 * (i / 2) + 0.2);
	item->anim->fct(item->anim);
	glCallList(g_env->lists[_init_item_pos]);
	glDrawElements(GL_TRIANGLES, sizes[_vbo_indx], GL_UNSIGNED_SHORT, 0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	i = (i + 1) % 4;
}

void		display_any(t_item *item)
{
	GLuint	*vbos;
	int		*sizes;

	glDisable(GL_LIGHTING);
	vbos = g_env->vbos[item->vbo];
	sizes = g_env->vbosizes[item->vbo];
	glBindBuffer(GL_ARRAY_BUFFER, vbos[_vbo_vrtx]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[_vbo_nrms]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[_vbo_indx]);
	glPushMatrix();
	glCallList(item->list);
	item->anim->fct(item->anim);
	glDrawElements(GL_TRIANGLES, sizes[_vbo_indx], GL_UNSIGNED_SHORT, 0);
	glPopMatrix();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glEnable(GL_LIGHTING);
}

void		display_items(int num)
{
	int			i;
	t_uchar		*grid;
	t_list		*list;
	t_list		**tmp;

	i = 0;
	tmp = &g_env->sq[num].anims;
	grid = g_env->sq[num].grid;
	list = g_env->sq[num].egg;
	display_all_stones(g_env->sq + num);
	while (list)
	{
		display_egg(grid[i++ % CASE_MAX_ITEMS]);
		list = list->next;
	}
	display_all_food(g_env->sq + num);
	while (*tmp)
	{
		((t_item *)(*tmp)->content)->fct((*tmp)->content);
		if (ACC_ITM(*tmp)->vbo == _mod_talk && ACC_ITM(*tmp)->anim->dead)
			del_link(tmp, del_item);
		if (*tmp)
			tmp = &(*tmp)->next;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
