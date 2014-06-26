/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_gfx_send.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 17:21:48 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/26 17:49:02 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void		gfx_send_egg(t_env *e, t_egg *egg, void (*fu)())
{
	t_glst	*tmp;

	tmp = e->srv.glst;
	while (tmp)
	{
		fu(e, tmp->cs, egg);
		tmp = tmp->next;
	}
}

void		gfx_send_npc(t_env *e, int cs, void (*fu)())
{
	t_glst	*tmp;

	tmp = e->srv.glst;
	while (tmp)
	{
		fu(e, tmp->cs, cs);
		tmp = tmp->next;
	}
}

void		gfx_send_act(t_env *e, int cs, void (*fu)(), int itm)
{
	t_glst	*tmp;

	tmp = e->srv.glst;
	while (tmp)
	{
		fu(e, tmp->cs, cs, itm);
		tmp = tmp->next;
	}
}

void		gfx_send_map(t_env *e, int x, int y, void (*fu)())
{
	t_glst	*tmp;

	tmp = e->srv.glst;
	while (tmp)
	{
		fu(e, tmp->cs, x, y);
		tmp = tmp->next;
	}
}

void		gfx_send_pcb(t_env *e, int clt, char *msg, void (*fu)())
{
	t_glst	*tmp;

	tmp = e->srv.glst;
	while (tmp)
	{
		fu(e, tmp->cs, clt, msg);
		tmp = tmp->next;
	}
}
