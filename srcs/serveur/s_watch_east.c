/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_watch_east.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/14 20:26:22 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/15 17:36:35 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>

void	find_east_line(t_env *e, int xy[2])
{
	if (xy[0] == 0)
		xy[0] = e->opt.x - 1;
	else
		xy[0]--;
	xy[1] = (xy[1] + 1) % e->opt.y;
}

void	east_case(t_env *e, int cs, int nb_case, int xy[2])
{
	int		i;
	int		x;
	int		y;

	i = 0;
	x = xy[0];
	y = xy[1];
	while (i < nb_case)
	{
		send_one_case(e, cs, x, y);
		if (((i + 1) - (e->users[cs]->player.lvl * 2)) != 1)
			tmp_to_bc(&e->users[cs]->buf_write, ", ", 0);
		y = (y + 1) % e->opt.y;
		i++;
	}
}

void	watch_east(t_env *e, int cs)
{
	int		i;
	int		j;
	int		xy[2];

	i = 0;
	j = 1;
	xy[0] = e->users[cs]->player.x;
	xy[1] = e->users[cs]->player.y;
	while (i < (e->users[cs]->player.lvl + 1))
	{
		east_case(e, cs, j, xy);
		find_east_line(e, xy);
		j += 2;
		i++;
	}
}
