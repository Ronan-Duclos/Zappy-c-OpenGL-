/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_lists.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/14 23:52:52 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/15 02:05:41 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "common.h"
#include "gfx_gl.h"

t_list	*new_link(t_list *next, void *content)
{
	t_list	*new;

	new = (t_list *)XV(NULL, malloc(sizeof(t_list)), "malloc");
	new->next = next;
	new->content = content;
	return (new);
}

void	del_link(t_list *link, t_list **list)
{
	t_list	*prev;
	t_list	*tmp;

	tmp = *list;
	prev = NULL;
	while (tmp && tmp != link)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (list)
	{
		if (prev)
			prev->next = tmp->next;
		else
			(*list = tmp->next);
		free(((t_item *)tmp->content)->anim);
		free(tmp->content);
		free(tmp);
	}
}
