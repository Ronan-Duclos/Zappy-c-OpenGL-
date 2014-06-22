/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_take_item.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 19:01:46 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/19 19:01:51 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>

void	take_item(t_env *e)
{
	int				a_read;
	t_actions		*acts;

	a_read = e->user->player.cur_aread;
	acts = &e->user->player.acts[a_read];
	if (acts->answer[0] == 'o' && acts->answer[1] == 'k')
	{
		if (acts->cmd[0] == 'l')
			e->user->player.ia.inv[_linemate]++;
		else if (acts->cmd[0] == 'd')
			e->user->player.ia.inv[_deraumere]++;
		else if (acts->cmd[0] == 's')
			e->user->player.ia.inv[_sibur]++;
		else if (acts->cmd[0] == 'm')
			e->user->player.ia.inv[_mendiane]++;
		else if (acts->cmd[0] == 'p')
			e->user->player.ia.inv[_phiras]++;
		else if (acts->cmd[0] == 't')
			e->user->player.ia.inv[_thystame]++;
	}
	acts->time = 0;
}

void	send_take_item(t_env *e, char *item)
{
	int			a_write;
	t_actions	*acts;
	char		buf[BUF_SIZE];

	strcpy(buf, "prend ");
	strcpy(buf + 6, item);
	a_write = e->user->player.cur_awrite;
	acts = &e->user->player.acts[a_write];
	acts->time = 1;
	acts->cmd = ft_strdup(buf);
	acts->fct_cmd = take_item;
	tmp_to_bc(&e->user->buf_write, buf, 1);
	e->user->player.cur_awrite = (e->user->player.cur_awrite + 1) % 10;
}
