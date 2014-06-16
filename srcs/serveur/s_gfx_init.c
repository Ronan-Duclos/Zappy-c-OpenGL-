/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_gfx_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/16 11:46:51 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/16 15:23:54 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void		gfx_end_init(t_env *e)
{
	t_glst	*tmp;

	tmp = e->srv.glst;
	while (tmp)
	{
		if (!e->users[tmp->cs]->ig)
			gfx_init(e, tmp->cs);
		tmp = tmp->next;
	}
}

void		gfx_init_send_tna(t_env *env, int cs)
{
	gfx_tna(env, cs);
	env->users[cs]->gfx.state++;
}

void		gfx_init_send_pnw(t_env *env, int cs)
{
	int		i;

	i = -1;
	while (++i < env->srv.max_fd)
	{
		if (env->users[i]->type == FD_CLT && !env->users[i]->gfx.gfx)
			gfx_pnw(env, cs, i);
	}
}

void		gfx_init(t_env *e, int cs)
{
	t_glst		*new;

	e->users[cs]->gfx.gfx = 1;
	if (!e->users[cs]->gfx.state)
	{
		new = NULL;
		e->users[cs]->player.team = NULL;
		new = glst_new(cs);
		glst_add(&e->srv.glst, new);
		gfx_msz(e, cs);
		gfx_sgt(e, cs);
		e->users[cs]->gfx.state += 1;
	}
	if (e->users[cs]->gfx.state == 1 && !e->users[cs]->ig)
		gfx_mct(e, cs);
	else if (e->users[cs]->gfx.state == 2)
		gfx_init_send_tna(e, cs);
	else if (e->users[cs]->gfx.state == 3)
	{
		gfx_init_send_pnw(e, cs);
		gfx_enw(e, cs);
		e->users[cs]->ig = 1;
	}
}
