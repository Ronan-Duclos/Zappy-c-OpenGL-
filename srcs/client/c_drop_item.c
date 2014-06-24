/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_drop_item.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 18:57:09 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/24 17:46:56 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>

void	drop_item(t_env *e)
{
	int			a_read;
	t_actions	*acts;

	a_read = e->user->player.cur_aread;
	acts = &e->user->player.acts[a_read];
	if (acts->answer[0] == 'o' && acts->answer[1] == 'k')
	{
		if (acts->cmd[0] == 'l' && e->user->player.ia.inv[_linemate] != 0)
			e->user->player.ia.inv[_linemate]--;
		else if (acts->cmd[0] == 'd' && e->user->player.ia.inv[_linemate] != 0)
			e->user->player.ia.inv[_deraumere]--;
		else if (acts->cmd[0] == 's' && e->user->player.ia.inv[_deraumere] != 0)
			e->user->player.ia.inv[_sibur]--;
		else if (acts->cmd[0] == 'm' && e->user->player.ia.inv[_sibur] != 0)
			e->user->player.ia.inv[_mendiane]--;
		else if (acts->cmd[0] == 'p' && e->user->player.ia.inv[_mendiane] != 0)
			e->user->player.ia.inv[_phiras]--;
		else if (acts->cmd[0] == 't' && e->user->player.ia.inv[_phiras] != 0)
			e->user->player.ia.inv[_thystame]--;
	}
	acts->time = 0;
	acts->wait = 0;
}


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
	acts->fct_cmd = drop_item;
	tmp_to_bc(&e->user->buf_write, buf, 1);
	e->user->player.cur_awrite = (e->user->player.cur_awrite + 1) % 10;
}
