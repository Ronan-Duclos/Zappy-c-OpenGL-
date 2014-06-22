/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_fork.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/16 21:11:49 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/22 12:59:20 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>
#include <libft.h>

t_egg		*egg_available(double time, t_egg *lst)
{
	while (lst)
	{
		if (lst->eclos > time)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void		add_egg(t_env *e, int cs)
{
	t_egg		*new;
	t_player	*p;
	t_egg		*tmp;
	int			i;

	new = (t_egg *)XV("NULL", malloc(sizeof(t_egg)), "malloc");
	bzero(new, sizeof(t_egg));
	p = &e->users[cs]->player;
	new->x = p->x;
	new->y = p->y;
	new->next = NULL;
	new->eclos = ft_usec_time() + 600 * (1000000 / e->opt.time);
	i = 0;
	while (strcmp(e->team[i].name, p->team) != 0)
		i++;
	tmp = e->team[i].eggs;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
	{
		new->id = tmp->id + 1;
		tmp->next = new;
	}
	else
	{
		e->team[i].eggs = new;
		new->id = 1;
	}
	printf("new egg team, id %d, x %d, y %d\n", new->id, new->x, new->y);
}

void	my_fork(t_env *e, int cs)
{
	int		i;

	i = -1;
	while (e->opt.name[++i] != NULL)
		if (ft_strcmp(e->users[cs]->player.team, e->team[i].name) == 0)
		{
			if (e->team[i].member < ((e->srv.max_fd - 4) / 3))
			{
				tmp_to_bc(&e->users[cs]->buf_write, "ok", 1);
				e->team[i].member++;
			}
			else
				tmp_to_bc(&e->users[cs]->buf_write, "ko", 1);
		}
}

void	gfx_fork(t_env *e, int cs)
{
	gfx_send_npc(e, cs, gfx_pfk);
}
