/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_display_items.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 20:45:06 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/13 21:00:05 by caupetit         ###   ########.fr       */
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

void		display_items(int sq)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < 7)
	{
		glCallList(g_env->lists[j]);
		while (i < CASE_MAX_ITEMS)
		{
			if (g_env->sq[sq].grid[i] == j)
			{
				if (sq == g_env->selectcase) // pareil
					display_egg(i, 1);
				else
					display_egg(i, 0);
			}
			i++;
		}
		i = 0;
		j++;
	}
}
