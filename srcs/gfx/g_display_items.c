/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_display_items.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 20:45:06 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/22 17:32:34 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "gfx_gl.h"
#include "mdx.h"

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
	list = sq->anims;
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
	grid = sq->grid;
	while (i < sq->itms[_food])
		display_food(grid[i++]);
	i = 0;
	j++;

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);

	while (list)
	{
		display_any(list->content);
		list = list->next;
	}
}
