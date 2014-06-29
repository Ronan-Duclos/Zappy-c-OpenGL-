/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_goto_bc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/25 18:39:05 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/27 00:12:55 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>

void		goto_bc(t_env *e)
{
	int			dir;

	dir = e->user->player.ia.bdc;
	if (dir == 4 || dir == 5)
		add_todo(e, send_turn_left, NULL);
	else if (dir == 6)
		add_todo(e, send_turn_right, NULL);
	if (dir == 2 || dir == 8 || dir == 4 || dir == 6)
		add_todo(e, send_move_forward, NULL);
	if (dir == 3 || dir == 2 || dir == 5)
		add_todo(e, send_turn_left, NULL);
	else if (dir == 8 || dir == 7)
		add_todo(e, send_turn_right, NULL);
	if (dir == 1 || dir == 3 || dir == 7 || dir == 5)
		add_todo(e, send_move_forward, NULL);
	else if (dir == 0)
	{
		if (player_ok(&e->user->player.ia))
			add_todo(e, send_incantation, NULL);
		else
			add_todo(e, send_broadcast, make_broadcast(&e->user->player.ia));
	}
	if (e->user->player.ia.msg)
		free(e->user->player.ia.msg);
	e->user->player.ia.msg = NULL;
	e->user->player.ia.bdc = -1;
}
