/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_item_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/15 01:11:11 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/24 19:06:49 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "gfx_gl.h"
#include "common.h"

/*
**	Creates a new item to be displayed, according to the params.
**	list is the list of transformations performed by OpenGL.
**	vbo is the model id.
**	anim is a pointer on the animation structure.
*/
t_item		*new_item(GLuint list, GLuint vbo, t_anim *a, void (*f)(t_item *))
{
	t_item	*new;

	new = (t_item *)XV(NULL, malloc(sizeof(t_item)), "malloc");
	new->list = list;
	new->vbo = vbo;
	new->anim = a;
	new->fct = f;
	return (new);
}

/*
**
*/
void		take_stone(int square, int stone)
{
	t_anim		*anim;
	t_item		*item;
	GLuint		list;
	int			i;
	t_square	*sq;
	static int	offsets[] = {FOOD_OFFSET, LINEMATE_OFFSET, DERAUMERE_OFFSET,
							SIBUR_OFFSET, MENDIANE_OFFSET, PHIRAS_OFFSET,
							THYSTAME_OFFSET};

	sq = g_env->sq + square;
	if (!sq->itms[stone])
		return ;
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
	item = new_item(list, _mod_stone, anim, &display_any);
	sq->anims = new_link(sq->anims, item);
	sq->itms[stone]--;
}
