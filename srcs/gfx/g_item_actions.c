/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_item_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/15 01:11:11 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/16 23:55:58 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "gfx_gl.h"
#include "common.h"

t_item		*new_item(GLuint list, GLuint id_nb, GLuint vbo, t_anim *anim)
{
	t_item	*new;

	new = (t_item *)XV(NULL, malloc(sizeof(t_item)), "malloc");
	new->list = list;
	new->id_nb = id_nb;
	new->vbo = vbo;
	new->anim = anim;
	return (new);
}

/*
**	Pas mal, c'est joli. Par contre la premiere pierre prise n'est pas la bonne.
**	A voir... Sinon ca lagouille un poil, ou plutot ca saute une frame de temps
**	en temps mais bon. Osef?
*/
void		take_stone(int square, int stone)
{
	t_anim	*anim;
	t_item	*item;
	GLuint	list;
	int		i;
	t_square	*sq;
	static int	offsets[] = {FOOD_OFFSET, LINEMATE_OFFSET, DERAUMERE_OFFSET,
							 SIBUR_OFFSET, MENDIANE_OFFSET, PHIRAS_OFFSET};

	sq = g_env->sq + square;
	if (!sq->itms[stone]) // A virer, ca sert a rien puisque c'est le serveur qui gere.
		return ; // Normalement ...
	i = sq->grid[offsets[stone] + sq->itms[stone]];
	list = glGenLists(1);
	glNewList(list, GL_COMPILE);
	{
		glCallList(g_env->lists[stone]);
		glTranslatef(1.9 / 16.0 * (i % 16) + 0.1, 0.0, 1.9 / 16 * (i / 16) + 0.1);
		glCallList(g_env->lists[_init_item_pos]);
	}
	glEndList();
	anim = new_anim(0, 500, &anim_rock);
	item = new_item(list, g_env->vbosizes[_mod_stone][_vbo_indx], g_env->vbos[_mod_stone][_vbo_indx], anim);
	g_env->sq[square].anims = new_link(g_env->sq[square].anims, item);
	g_env->sq[square].itms[stone]--;
}
