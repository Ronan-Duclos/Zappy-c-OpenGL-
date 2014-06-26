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

				printf("TAKE ITEM %d: %s, befor on : %d, with in my %d\n", i, acts->cmd,
					   e->user->player.ia.view[0][i], e->user->player.ia.inv[i]);
				e->user->player.ia.view[0][i]--;
				e->user->player.ia.inv[i]++;
				break ;
			}
		}
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
