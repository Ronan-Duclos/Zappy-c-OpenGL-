/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_fork.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/16 21:11:49 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/26 23:12:09 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>
#include <libft.h>

void			del_egg(t_team *team)
{
	t_egg			*egg;
	t_egg			*tmp;

	egg = team->eggs;
	if (egg)
	{
		tmp = egg->next;
		team->eggs = tmp;
		free(egg);
	}
}

t_egg			*new_egg(int x, int y, int cs)
{
	t_egg			*new;

	new = (t_egg *)XV("NULL", malloc(sizeof(t_egg)), "malloc");
	bzero(new, sizeof(t_egg));
	new->x = x;
	new->y = y;
	new->cs = cs;
	return (new);
}

void			add_egg(t_env *e, int cs)
{
	t_egg			*new;
	t_player		*p;
	t_egg			*tmp;
	static int		id;
	int				i;

	p = &e->users[cs]->player;
	new = new_egg(p->x, p->y, cs);
	new->food = NB_START_FOOD;
	new->next = NULL;
	new->t_eclos = ft_usec_time() + 600 * (1000000 / e->opt.time);
	new->t_last = ft_usec_time();
	i = 0;
	while (strcmp(e->team[i].name, p->team) != 0)
		i++;
	tmp = e->team[i].eggs;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	else
		e->team[i].eggs = new;
	new->id = ++id;
	gfx_send_egg(e, new, gfx_enw);
}

void			my_fork(t_env *e, int cs)
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
				add_egg(e, cs);
			}
			else
				tmp_to_bc(&e->users[cs]->buf_write, "ko", 1);
		}
}

void			gfx_fork(t_env *e, int cs)
{
	gfx_send_npc(e, cs, gfx_pfk);
}
