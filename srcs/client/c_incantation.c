/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_incantation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 19:00:17 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/22 20:54:51 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>

void	incantation(t_env *e)
{
	int			ar;
	t_actions	*act;
	int			lvl;

	ar = e->user->player.cur_aread;
	act = &e->user->player.acts[ar];
	lvl = ft_atoi(act->answer);
	if (lvl == e->user->player.ia.lvl)
		e->user->player.ia.lvlup = 0;
	else
		e->user->player.ia.lvl = lvl;
	act->time = 0;
}

void	send_incantation(t_env *e)
{
	int			a_write;
	t_actions	*acts;

	a_write = e->user->player.cur_awrite;
	acts = &e->user->player.acts[a_write];
	e->user->player.ia.lvlup = 1;
	acts->time = 1;
	acts->fct_cmd = incantation;
	tmp_to_bc(&e->user->buf_write, "incantation", 1);
	e->user->player.cur_awrite = (e->user->player.cur_awrite + 1) % 10;
}
