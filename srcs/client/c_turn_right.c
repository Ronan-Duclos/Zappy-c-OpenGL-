/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_turn_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 19:02:26 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/19 19:02:30 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>

void	send_turn_right(t_env *e)
{
	int			a_write;
	t_actions	*acts;

	a_write = e->user->player.cur_awrite;
	acts = &e->user->player.acts[a_write];
	acts->time = 1;
	acts->cmd = ft_strdup("droite");
	acts->fct_cmd = receive_ok_only;
	tmp_to_bc(&e->user->buf_write, acts->cmd, 1);
	e->user->player.cur_awrite = (e->user->player.cur_awrite + 1) % 10;
}
