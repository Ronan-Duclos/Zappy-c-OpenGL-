/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_display_items.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 20:45:06 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/14 01:45:57 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "gfx_gl.h"
#include "mdx.h"

static void	display_egg(int i, int testo) // Attention
{
	static t_anim test = {0, 500, NULL, 0}; // A virer

	glPushMatrix();
	glTranslatef(1.9 / 16.0 * (i % 16) + 0.1, 0.0, 1.9 / 16 * (i / 16) + 0.1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_env->vbo_indx);
	glCallList(g_env->lists[_init_item_pos]);
	if (testo)
		anim_rock(&test); //// Idem
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
	static int	tab[] = {
		FOOD_PER_SQUARE,
		LINEMATE_PER_SQUARE,
		DERAUMERE_PER_SQUARE,
		SIBUR_PER_SQUARE,
		MENDIANE_PER_SQUARE,
		PHIRAS_PER_SQUARE,
		THYSTAME_PER_SQUARE};

	sq = g_env->sq + num;
	grid = sq->grid;
	i = 0;
	j = 0;
	while (j < 7)
	{
		glCallList(g_env->lists[j]);
		while (i < sq->itms[j])
		{
			if (num == g_env->selectcase) // pareil
				display_egg(grid[i], 1); // Putain
			else
				display_egg(grid[i], 0); // LOL le mec ...
			i++;
		}
		grid += tab[j];
		i = 0;
		j++;
	}
}
