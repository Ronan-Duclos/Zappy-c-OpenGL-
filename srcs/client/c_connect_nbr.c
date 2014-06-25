/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_connect_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 18:57:19 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/25 04:21:05 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>

void	connect_nbr(t_env *e)
{
	int			ar;
	t_actions	*act;

	ar = e->user->player.cur_aread;
	act = &e->user->player.acts[ar];
	e->user->player.ia.c_nbr = ft_atoi(act->answer);
	act->time = 0;
}

void	send_connect_nbr(t_env *e)
{
	int			a_write;
	t_actions	*acts;

	a_write = e->user->player.cur_awrite;
	acts = &e->user->player.acts[a_write];
	acts->time = 1;
	acts->fct_cmd = connect_nbr;
	acts->cmd = ft_strdup("connect_nbr");
	tmp_to_bc(&e->user->buf_write, acts->cmd, 1);
	e->user->player.cur_awrite = (e->user->player.cur_awrite + 1) % 10;
}
