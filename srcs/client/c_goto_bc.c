/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_goto_bc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/25 18:39:05 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/26 00:00:00 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>

void		goto_bc(t_env *e)
{
	int			dir;
	printf("recv bdc %d %s\n", e->user->player.ia.bdc, e->user->player.ia.msg);
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
		add_todo(e, send_incantation, NULL);
	free(e->user->player.ia.msg);
	e->user->player.ia.msg = NULL;
	e->user->player.ia.bdc = -1;
}
