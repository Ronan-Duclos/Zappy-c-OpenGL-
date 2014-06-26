/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_broadcast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 18:56:12 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/26 23:32:08 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>

char	*make_broadcast(t_ia *ia)
{
	static char		buf[20];

	bzero(buf, 20);
	sprintf(buf, "%d", ia->lvl);
	return (buf);
}

void	send_broadcast(t_env *e, char *msg)
{
	int				a_write;
	t_actions		*acts;
	static char		buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	strcpy(buf, "broadcast ");
	strcpy(buf + 10, msg);
	a_write = e->user->player.cur_awrite;
	acts = &e->user->player.acts[a_write];
	acts->time = 0;
	acts->cmd = ft_strdup(buf);
	acts->fct_cmd = receive_ok_only;
	tmp_to_bc(&e->user->buf_write, buf, 1);
	e->user->player.cur_awrite = (e->user->player.cur_awrite + 1) % 10;
}
