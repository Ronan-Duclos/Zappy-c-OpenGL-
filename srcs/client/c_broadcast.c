/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_broadcast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 18:56:12 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/19 18:56:17 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>

void	send_broadcast(t_env *e, char *msg)
{
	int			a_write;
	t_actions	*acts;
	char		buf[BUF_SIZE];

	strcpy(buf, "broadcast ");
	strcpy(buf + 10, msg);
	a_write = e->user->player.cur_awrite;
	acts = &e->user->player.acts[a_write];
	acts->time = 1;
	acts->cmd = ft_strdup(buf);
	/*acts->fct_cmd = my_broadcast;*/
	tmp_to_bc(&e->user->buf_write, buf, 1);
	e->user->player.cur_awrite = (e->user->player.cur_awrite + 1) % 10;
}
