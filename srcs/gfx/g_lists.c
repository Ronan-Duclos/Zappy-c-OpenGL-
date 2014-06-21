/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_lists.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/14 23:52:52 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/21 18:57:42 by tmielcza         ###   ########.fr       */
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

void	del_link(t_list **link, void (*ft)(void *))
{
	t_list	*tmp;

	tmp = *link;
	*link = (*link)->next;
	ft(tmp->content);
	free(tmp);
}

void	switch_link(t_list **src, t_list **dst)
{
	t_list	*tmp;

	if (*src == *dst)
		return ;
	tmp = *dst;
	*dst = *src;
	(*dst)->next = tmp;
	*src = (*src)->next;
}
