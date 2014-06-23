/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 21:48:32 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/23 16:22:05 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "common.h"

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
	e->user->player.ia.lvl = 1;
	e->user->player.ia.expulsed = 1;
	e->user->player.ia.c_nbr = 0;
	e->user->player.ia.view = NULL;
	e->user->player.ia.lvlup = 0;
	init_bc(&e->user->buf_read);
	init_bc(&e->user->buf_write);
}
