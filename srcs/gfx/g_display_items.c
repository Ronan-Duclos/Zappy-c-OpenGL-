/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_display_items.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 22:26:42 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/26 05:31:36 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "gfx_gl.h"
#include "mdx.h"

void		display_egg(int i)
{
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
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
	glDrawElements(GL_TRIANGLES, g_env->vbosizes[_mod_egg][_vbo_indx], GL_UNSIGNED_SHORT, 0);

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	i = (i + 1) % 4;
}

void		display_any(t_item *item)
{
	GLuint	*vbos;
	int		*sizes;

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
}

static void	display_food(int i)
{
	glPushMatrix();
	glTranslatef(1.9 / 16.0 * (i % 16) + 0.1, 0.0, 1.9 / 16 * (i / 16) + 0.1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_env->vbos[_mod_plant][_vbo_indx]);
	glCallList(g_env->lists[_init_plant_pos]);
	glDrawElements(GL_TRIANGLES, g_env->vbosizes[_mod_plant][_vbo_indx], GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glPopMatrix();
}

static void	display_stone(int i)
{
	glPushMatrix();
	glTranslatef(1.9 / 16.0 * (i % 16) + 0.1, 0.0, 1.9 / 16 * (i / 16) + 0.1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_env->vbos[_mod_stone][_vbo_indx]);
	glCallList(g_env->lists[_init_item_pos]);
	glDrawElements(GL_TRIANGLES, g_env->vbosizes[_mod_stone][_vbo_indx], GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glPopMatrix();
}

void		display_items(int num)
{
	int			i;
	int			j;
	t_square	*sq;
	unsigned char	*grid;
	t_list			*list;
	static int	tab[] = {
		FOOD_PER_SQUARE, LINEMATE_PER_SQUARE, DERAUMERE_PER_SQUARE,
		SIBUR_PER_SQUARE, MENDIANE_PER_SQUARE, PHIRAS_PER_SQUARE,
		THYSTAME_PER_SQUARE};

	sq = g_env->sq + num;
	grid = sq->grid + tab[0];
	i = 0;
	j = 1;

	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_stone][_vbo_vrtx]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_stone][_vbo_nrms]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	while (j < 7)
	{
		glCallList(g_env->lists[j]);
		while (i < sq->itms[j])
			display_stone(grid[i++]);
		grid += tab[j];
		i = 0;
		j++;
	}

	i = 0;
	j = 7;
	grid = sq->grid;
	list = sq->egg;
	while (list)
	{
		display_egg(grid[i++ % CASE_MAX_ITEMS]);
		list = list->next;
	}

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glCallList(g_env->lists[_white]);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_plant][_vbo_texp]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_plant][_vbo_vrtx]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_plant][_vbo_nrms]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, g_env->testex);

	j = 0;
	i = 0;
	grid = sq->grid;
	while (i < sq->itms[_food])
		display_food(grid[i++]);
	i = 0;

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);

	t_list	**tmp = &sq->anims;
	while (*tmp)
	{
		((t_item *)(*tmp)->content)->fct((*tmp)->content);
		if (((t_item *)(*tmp)->content)->vbo == _mod_stone && ((t_item *)(*tmp)->content)->anim->dead)
			del_link(tmp, del_item);
		if (*tmp)
			tmp = &(*tmp)->next;
	}
}
