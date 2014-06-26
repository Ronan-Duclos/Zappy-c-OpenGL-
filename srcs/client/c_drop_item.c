/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_drop_item.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 18:57:09 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/26 23:32:38 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>

void	drop_item(t_env *e)
{
	int				a_read;
	t_actions		*acts;
	char			cmd[7] = "nldsmpt";
	int				i;

	i = -1;
	a_read = e->user->player.cur_aread;
	acts = &e->user->player.acts[a_read];
	if (acts->answer[0] == 'o' && acts->answer[1] == 'k')
	{
		while (++i < 7)
		{
			if (acts->cmd[6] == cmd[i])
			{
				e->user->player.ia.inv[i]++;
				break ;
			}
		}
	}
	acts->time = 0;
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
