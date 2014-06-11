/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_generate_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 15:09:24 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/11 12:06:19 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <libft.h>
#include <common.h>
#include <serveur.h>
#include <conf.h>

int				put_one(t_env *env, int type_rate[2], int x, int y)
{
	int		r;

	r = 0;
	if (type_rate[1] > 0 && rand_int(0, 100) <= type_rate[1])
	{
		env->map[x][y][type_rate[0]]++;
		r++;
		type_rate[1] -= 5;
		if (x == 0)
			r += put_one(env, type_rate, env->opt.x - 1, y);
		else
			r += put_one(env, type_rate, x - 1, y);
		r += put_one(env, type_rate, (x + 1) % env->opt.x, y);
		r += put_one(env, type_rate, x, (y + 1) % env->opt.y);
		if (y == 0)
			r += put_one(env, type_rate, x, env->opt.y - 1);
		else
			r += put_one(env, type_rate, x, y - 1);
	}
	return (r);
}

int				get_quantity_by_type(t_env *env, int type)
{
	int				nb_cell;
	static int		base_nb[NB_STONE + 1] = {

	NB_FOOD,
	NB_LINEMATE,
	NB_DERAUMERE,
	NB_SIBUR,
	NB_MENDIANE,
	NB_PHIRAS,
	NB_THYSTAME};
	nb_cell = env->opt.x * env->opt.y;
	return (nb_cell / base_nb[type]);
}

int				put_stones(t_env *env)
{
	int				type_rate[2];
	int				quantity;
	int				x;
	int				y;
	int				c;
	static int		base_rate[NB_STONE + 1] = {

	RATE_FOOD,
	RATE_LINEMATE,
	RATE_DERAUMERE,
	RATE_SIBUR,
	RATE_MENDIANE,
	RATE_PHIRAS, 
	RATE_THYSTAME};
	type_rate[0] = 0;
	while (type_rate[0] < NB_STONE + 1)
	{
		quantity = get_quantity_by_type(env, type_rate[0]);
		c = 0;
		while (quantity--)
		{
			type_rate[1] = base_rate[type_rate[0]];
			x = rand_int(0, env->opt.x);
			y = rand_int(0, env->opt.y);
			c += put_one(env, type_rate, x, y);
		}
		printf("%d items de type %d ont ete poses.\n", c, type_rate[0]);
		type_rate[0]++;
	}
	return (0);
}

t_map			malloc_map(int x, int y)
{
	t_inv		**map;
	int			i;

	map = (t_inv **)malloc(sizeof(t_inv *) * (x + 1));
	i = 0;
	while (i < x)
	{
		map[i] = (t_inv *)malloc(sizeof(t_inv) * (y + 1));
		ft_bzero(map[i], sizeof(t_inv *));
		i++;
	}
	map[x] = NULL;
	return ((t_map)map);
}

t_map			generate_map(t_env *env, int x, int y)
{
	t_map		map;

	map = (t_map)malloc_map(x, y);
	env->map = map;
	put_stones(env);
	printf("GENERATION MAP COMPLETE\n");
	return (map);
}

