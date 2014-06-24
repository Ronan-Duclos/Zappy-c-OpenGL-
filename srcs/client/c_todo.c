/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_todo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/23 21:48:43 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/24 19:25:57 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <stdlib.h>

void		add_todo(t_env *e, void (*f)(), char *msg)
{
	t_todo			*new;
	t_todo			*tmp;

	new = (t_todo *)XV(NULL, malloc(sizeof(t_todo)), "malloc");
	new->msg = msg;
	new->fct_send = f;
	new->next = NULL;
	tmp = e->user->player.ia.todo;
	if (tmp == NULL)
		e->user->player.ia.todo = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void		todo_to_cal(t_env *e)
{
	int			*aw;

	aw = &e->user->player.cur_awrite;
	while (e->user->player.acts[*aw].time == 0)
	{
		if (e->user->player.ia.todo != NULL)
		{
			printf("TRY_TO_SEND\n");
			if (e->user->player.ia.todo->msg == NULL)
				e->user->player.ia.todo->fct_send(e);
			else
				e->user->player.ia.todo->fct_send(e, e->user->player.ia.todo->msg);
			del_todo(e);
		}
	}
}

void		del_todo(t_env *e)
{
	t_todo			*tmp;

	tmp = e->user->player.ia.todo;
	e->user->player.ia.todo = tmp->next;
	free(tmp);
}
