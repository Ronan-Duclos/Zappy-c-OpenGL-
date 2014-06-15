/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_display_items.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 20:45:06 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/15 02:13:58 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "gfx_gl.h"
#include "mdx.h"

void		display_any(t_item *item)
{
	glPushMatrix();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, item->vbo);
	glCallList(item->list);
	item->anim->fct(item->anim);
	glDrawElements(GL_TRIANGLES, item->id_nb, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glPopMatrix();
}

static void	display_egg(int i)
{
	glPushMatrix();
	glTranslatef(1.9 / 16.0 * (i % 16) + 0.1, 0.0, 1.9 / 16 * (i / 16) + 0.1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_env->vbo_indx);
	glCallList(g_env->lists[_init_item_pos]);
	glDrawElements(GL_TRIANGLES, g_mdx.chunks[_pvtx].nb, GL_UNSIGNED_SHORT, 0);
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
	grid = sq->grid;
	list = sq->anims;
	i = 0;
	j = 0;
	while (j < 7)
	{
		glCallList(g_env->lists[j]);
		while (i < sq->itms[j])
			display_egg(grid[i++]);
		grid += tab[j];
		i = 0;
		j++;
	}
	while (list)
	{
		display_any(list->content);
		list = list->next;
	}
}
