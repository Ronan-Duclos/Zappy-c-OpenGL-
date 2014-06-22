/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_inv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 19:00:38 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/19 19:03:53 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>

void	inventaire(t_env *e)
{
	int			ar;
	t_actions	*act;

	ar = e->user->player.cur_aread;
	act = &e->user->player.acts[ar];
	get_inventaire(e->user->player.ia.inv, act->answer);
	act->time = 0;
}

void	send_inventaire(t_env *e)
{
	int			a_write;
	t_actions	*acts;

	a_write = e->user->player.cur_awrite;
	acts = &e->user->player.acts[a_write];
	acts->time = 1;
	acts->cmd = ft_strdup("inventaire");
	acts->fct_cmd = inventaire;
	tmp_to_bc(&e->user->buf_write, acts->cmd, 1);
	e->user->player.cur_awrite = (e->user->player.cur_awrite + 1) % 10;
}
