/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_drop_item.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 18:57:09 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/19 18:58:29 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>

void	send_drop_item(t_env *e, char *item)
{
	int			a_write;
	t_actions	*acts;
	char		buf[BUF_SIZE];

	strcpy(buf, "pose ");
	strcpy(buf + 5, item);
	a_write = e->user->player.cur_awrite;
	acts = &e->user->player.acts[a_write];
	acts->time = 1;
	acts->cmd = ft_strdup(buf);
	/*acts->fct_cmd = send_item;*/
	tmp_to_bc(&e->user->buf_write, buf, 1);
	e->user->player.cur_awrite = (e->user->player.cur_awrite + 1) % 10;
}
