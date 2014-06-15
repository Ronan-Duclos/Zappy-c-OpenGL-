/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_watch_sight.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/14 19:25:34 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/14 20:10:40 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>

void	send_one_case(t_env *e, t_buf *bc, int x, int y)
{
	int		type;
	int		quantity;

	type = -1;
	while (++type < NB_STONE + 2)
	{
		quantity = e->map[x][y][type];
		while (quantity--)
		{
			tmp_to_bc(bc, type_to_str(type), 0);
			if (type != NB_STONE + 1 && quantity != 0)
				char_to_bc(bc, ' ');
		}
	}
}

void	watch_sight(t_env *e, int cs)
{
	if (e->users[cs]->player.direc == NORTH)
		watch_north(e, cs);
	else if (e->users[cs]->player.direc == EAST)
		watch_east(e, cs);
	else if (e->users[cs]->player.direc == SOUTH)
		watch_south(e, cs);
	else if (e->users[cs]->player.direc == WEST)
		watch_west(e, cs);
}
