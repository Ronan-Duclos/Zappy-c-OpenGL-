/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_gfx_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 16:00:49 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/12 18:48:06 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "serveur.h"

t_glst		*glst_new(int cs)
{
	t_glst	*new;

	new = (t_glst *)XV(NULL, malloc(sizeof(t_glst)), "glst_new");
	new->cs = cs;
	new->next = NULL;
	return (new);
}

void		glst_add(t_glst **lst, t_glst *new)
{
	t_glst	*tmp;

	if (!lst || !*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void		glst_del_one(t_glst **lst, int cs)
{
	t_glst	*tmp;
	t_glst	*prev;

	prev = NULL;
	tmp = *lst;
	if (tmp->cs == cs)
	{
		if (tmp->next)
			prev = tmp->next;
		free(tmp);
		*lst = prev;
		return ;
	}
	while (tmp && tmp->cs != cs)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	prev->next = tmp->next;
	free(tmp);
}

void		glst_put(t_glst **lst)
{
	t_glst	*tmp;

	tmp = *lst;
	while (tmp)
	{
		printf("list: %d\n", tmp->cs);
		tmp = tmp->next;
	}
}
