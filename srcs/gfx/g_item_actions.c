/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_item_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/15 01:11:11 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/27 00:15:41 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "gfx_gl.h"
#include "common.h"

void		del_item(void *item)
{
	t_item	*i;

	i = (t_item *)item;
	if (i->anim)
		free(i->anim);
	free(i);
}

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
