/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_gfx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 16:54:11 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/11 19:42:29 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "serveur.h"
#include "libft.h"

/*
**	send map_size;
*/
void		gfx_msz(t_env *e, int cs)
{
	char	buf[4096];

	ft_bzero(buf, 4096);
	sprintf(buf, "msz %d %d", e->opt.x, e->opt.y);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

/*
**	send time.
*/
void		gfx_sgt(t_env *e, int cs)
{
	char	buf[4096];

	ft_bzero(buf, 4096);
	sprintf(buf, "sgt %d", e->opt.time);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

/*
**	send invotory of map[X][Y]
*/
void		gfx_bct(t_env *e, int cs, int x, int y)
{
	char	buf[4096];

	printf("inventaire case:\n");
	printf("1 %d\n", e->map[x][y][_food]);
	printf("2 %d\n", e->map[x][y][_linemate]);
	printf("3 %d\n", e->map[x][y][_deraumere]);
	printf("4 %d\n", e->map[x][y][_sibur]);
	printf("5 %d\n", e->map[x][y][_mendiane]);
	printf("6 %d\n", e->map[x][y][_phiras]);
	printf("7 %d\n", e->map[x][y][_thystame]);
	ft_bzero(buf, 4096);
	sprintf(buf, "bct %d %d %d %d %d %d %d %d %d", x, y,
			e->map[x][y][_food],
			e->map[x][y][_linemate],
			e->map[x][y][_deraumere],
			e->map[x][y][_sibur],
			e->map[x][y][_mendiane],
			e->map[x][y][_phiras],
			e->map[x][y][_thystame]);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

/*
**	send map
*/
void		gfx_mct(t_env *e, int cs)
{
	int		i;
	int		j;

	i = -1;
	while (++i < e->opt.x)
	{
		j = -1;
		while (++j < e->opt.y)
			gfx_bct(e, cs, i, j);
	}
}

void		gfx_init(t_env *e, int cs)
{
	e->users[cs]->ig = 1;
	e->users[cs]->gfx = 1;
	e->users[cs]->player.team = NULL;
	gfx_msz(e, cs);
	gfx_sgt(e, cs);
	gfx_mct(e, cs);
}
