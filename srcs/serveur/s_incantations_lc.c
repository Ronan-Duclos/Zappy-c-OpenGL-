/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_incantations_lc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/27 05:46:05 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/27 08:13:10 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>
#include <serveur.h>
#include <common.h>

void	add_css_lc(t_env *e, int cs, int id)
{
	t_inc	*tmp;
	int		i;

	i = 0;
	tmp = e->incs;
	while (tmp->id != id)
		tmp = tmp->next;
	while (tmp->css[i] != 0)
		i++;
	tmp->css[i] = cs;
}

void	add_incs(t_env *e, int id, double time)
{
	t_inc		*new;
	t_inc		*tmp;

	new = (t_inc *)XV(NULL, malloc(sizeof(t_inc)), "malloc");
	new->id = id;
	new->time = time;
	bzero(new->css, 255);
	new->next = NULL;
	tmp = e->incs;
	if (tmp == NULL)
		e->incs = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	remove_incs(t_env *e, int id)
{
	t_inc		*del;
	t_inc		*tmp;

	tmp = e->incs;
	if (tmp->id == id)
	{
		del = e->incs;
		e->incs = e->incs->next;
	}
	else
	{
		while (tmp->next != NULL && tmp->next->id == id)
			tmp = tmp->next;
		del = tmp->next;
		tmp->next = del->next;
	}
	free(del);
}
