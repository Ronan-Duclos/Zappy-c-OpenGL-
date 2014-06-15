/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_watch_north.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/14 20:13:39 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/14 20:26:01 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>

void	find_north_line(t_env *e, int xy[2])
{
	if (xy[0] == 0)
		xy[0] = e->opt.x - 1;
	else
		xy[0]--;
	if (xy[1] == 0)
		xy[1] = e->opt.y - 1;
	else
		xy[1]--;
}

void	north_case(t_env *e, t_buf *bc, int nb_case, int xy[2])
{
	int		i;
	int		x;
	int		y;

	i = 0;
	x = xy[0];
	y = xy[1];
	while (i < nb_case)
	{
		send_one_case(e, bc, x, y);
		if (i != nb_case -1)
			tmp_to_bc(bc, ", ", 0);
		y = (y + 1) % e->opt.y;
		i++;
	}
}

void	watch_north(t_env *e, int cs)
{
	int		i;
	int		j;
	int		xy[2];

	i = 0;
	j = 1;
	xy[0] = e->users[cs]->player.x;
	xy[1] = e->users[cs]->player.y;
	while (i < e->users[cs]->player.lvl + 1)
	{
		north_case(e, &e->users[cs]->buf_write, j, xy);
		find_north_line(e, xy);
		j += 2;
		i++;
	}
}
