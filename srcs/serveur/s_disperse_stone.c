/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_disperse_stone.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 18:23:55 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/26 18:25:28 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <global.h>

void			disperse_stone(t_env *e, int cs, int good)
{
	int		nb_stone;
	int		i;
	int		x;
	int		y;

	if (good != 1)
		return ;
	i = 0;
	while (++i < 7)
	{
		x = e->users[cs]->player.x;
		y = e->users[cs]->player.y;
		nb_stone = g_lvlup[e->users[cs]->player.lvl - 1][i];
		while (nb_stone != 0)
		{
			e->map[y][x].ground[i]--;
			x = rand() % e->opt.x;
			y = rand() % e->opt.y;
			e->map[y][x].ground[i]++;
			gfx_send_map(e, x, y, gfx_bct);
			nb_stone--;
		}
	}
	e->users[cs]->player.acts[e->users[cs]->player.cur_aread].start = 0;
}
