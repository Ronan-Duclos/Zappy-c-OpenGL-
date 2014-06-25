/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 21:48:32 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/25 20:07:20 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "common.h"

void	init_ia(t_env *e)
{
	e->user->player.ia.need_stone[0] = 0;
	e->user->player.ia.need_stone[1] = 9;
	e->user->player.ia.need_stone[2] = 8;
	e->user->player.ia.need_stone[3] = 10;
	e->user->player.ia.need_stone[4] = 5;
	e->user->player.ia.need_stone[5] = 6;
	e->user->player.ia.need_stone[6] = 1;
	e->user->player.ia.lvl = 1;
	e->user->player.ia.expulsed = 0;
	e->user->player.ia.my_exp = 0;
	e->user->player.ia.c_nbr = 0;
	e->user->player.ia.bdc = 0;
	e->user->player.ia.msg = NULL;
	e->user->player.ia.view = NULL;
	e->user->player.ia.lvlup = 0;
}

void	init_clt(t_env *e)
{
	int		i;

	i = -1;
	e->user = (t_user *)XV(NULL, malloc(sizeof(t_user)), "malloc");
	e->user->ig = 0;
	e->user->player.cur_aread = 0;
	e->user->player.cur_awrite = 0;
	while (++i < 10)
	{
		e->user->player.acts[i].time = 0;
		e->user->player.acts[i].cmd = NULL;
	}
	init_ia(e);
	init_bc(&e->user->buf_read);
	init_bc(&e->user->buf_write);
}
