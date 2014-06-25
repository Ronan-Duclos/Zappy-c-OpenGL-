/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_expulse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 18:59:57 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/25 04:31:01 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>

void	my_expulse(t_env *e)
{
	int			ar;
	t_actions	*act;

	ar = e->user->player.cur_aread;
	act = &e->user->player.acts[ar];
	if (act->answer[0] == 'o')
		e->user->player.ia.my_exp = 1;
	else
		e->user->player.ia.my_exp = 0;
	act->time = 0;
}

void	send_expulse(t_env *e)
{
	int			a_write;
	t_actions	*acts;

	a_write = e->user->player.cur_awrite;
	acts = &e->user->player.acts[a_write];
	acts->time = 1;
	acts->cmd = ft_strdup("expulse");
	acts->fct_cmd = my_expulse;
	tmp_to_bc(&e->user->buf_write, acts->cmd, 1);
	e->user->player.cur_awrite = (e->user->player.cur_awrite + 1) % 10;
}
