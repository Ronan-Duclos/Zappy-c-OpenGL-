/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_display_things.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/27 07:37:48 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/27 07:41:26 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx_gl.h"

static void	display_food(int i)
{
	glPushMatrix();
	glTranslatef(1.9 / 16.0 * (i % 16) + 0.1, 0.0, 1.9 / 16 * (i / 16) + 0.1);
	glCallList(g_env->lists[_init_plant_pos]);
	glDrawElements(GL_TRIANGLES, g_env->vbosizes[_mod_plant][_vbo_indx],
				GL_UNSIGNED_SHORT, 0);
	glPopMatrix();
}

static void	display_stone(int i)
{
	glPushMatrix();
	glTranslatef(1.9 / 16.0 * (i % 16) + 0.1, 0.0, 1.9 / 16 * (i / 16) + 0.1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_env->vbos[_mod_stone][_vbo_indx]);
	glCallList(g_env->lists[_init_item_pos]);
	glDrawElements(GL_TRIANGLES, g_env->vbosizes[_mod_stone][_vbo_indx],
				GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glPopMatrix();
}

void		display_all_food(t_square *sq)
{
	int		i;
	t_uchar	*grid;

	glEnable(GL_TEXTURE_2D);
	glCallList(g_env->lists[_white]);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_plant][_vbo_texp]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_plant][_vbo_vrtx]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbos[_mod_plant][_vbo_nrms]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glBindTexture(GL_TEXTURE_2D, g_env->testex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_env->vbos[_mod_plant][_vbo_indx]);
	i = 0;
	grid = sq->grid;
	while (i < sq->itms[_food])
		display_food(grid[i++]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisable(GL_TEXTURE_2D);
}

void		display_all_stones(t_square *sq)
{
	int			i;
	int			j;
	t_uchar		*grid;
	static int	tab[] = {

	FOOD_PER_SQUARE, LINEMATE_PER_SQUARE, DERAUMERE_PER_SQUARE,
	SIBUR_PER_SQUARE, MENDIANE_PER_SQUARE, PHIRAS_PER_SQUARE,
	THYSTAME_PER_SQUARE};
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
}
