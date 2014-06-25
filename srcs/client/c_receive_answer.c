/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_receive_answer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/23 19:02:37 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/25 04:23:46 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>

void	receive_ok_only(t_env *e)
{
	int			ar;
	t_actions	*act;

	ar = e->user->player.cur_aread;
	act = &e->user->player.acts[ar];
	act->time = 0;
}
