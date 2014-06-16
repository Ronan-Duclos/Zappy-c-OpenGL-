/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_watch_sight.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/14 19:25:34 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/16 23:37:21 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>

void	send_one_case(t_env *e, int cs, int x, int y)
{
	int		type;
	int		quantity;
	int		i;

	type = -1;
	i = 0;
	while (++type < (NB_STONE + 2))
	{
		quantity = e->map[x][y].ground[type];
		if (type == _player 
			&& e->users[cs]->player.x == x
			&& e->users[cs]->player.y == y)
			quantity--;
		while (quantity--)
		{
			if (i != 0)
				char_to_bc(&e->users[cs]->buf_write, ' ');
			tmp_to_bc(&e->users[cs]->buf_write, type_to_str(type), 0);
			i++;
		}		
	}
}

void	watch_sight(t_env *e, int cs)
{
	char_to_bc(&e->users[cs]->buf_write, '{');
	if (e->users[cs]->player.direc == NORTH)
		watch_north(e, cs);
	else if (e->users[cs]->player.direc == EAST)
		watch_east(e, cs);
	else if (e->users[cs]->player.direc == SOUTH)
		watch_south(e, cs);
	else if (e->users[cs]->player.direc == WEST)
		watch_west(e, cs);
	tmp_to_bc(&e->users[cs]->buf_write, "}", 1);
}
