/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/30 12:19:56 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/06 18:39:07 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>
#include <libft.h>
#include <serveur.h>

#include <stdio.h>

/*			AFFIHACGE OPT
void			put_opt(t_opt *opt)
{
	int				i;

	ft_printf("port : %d\n", opt->port);
	ft_printf("x : %d\n", opt->x);
	ft_printf("y : %d\n", opt->y);
	i = -1;
	while (opt->name && opt->name[++i])
		ft_printf("%s\n", opt->name[i]);
	ft_printf("client : %d\n", opt->client);
	ft_printf("time : %d\n", opt->time);
}

//affichage map en fonction des pierres
void			print_stone(t_env *env, int type)
{
	int		x;
	int		y;
	int		i;
	int		j;

	x = env->opt.x;
	y = env->opt.y;
	i = 0;
	j = 0;
	printf("========== TYPE %d =========\n", type);
	while (j < y)
	{
		i = 0;
		while (i < x)
		{
			printf("|%2d", env->map[i][j][type]);
			i++;
		}
		j++;
		printf("\n");
	}
}
*/

void	run_serv(t_env *e)
{
	t_srv	*s;

	s = &e->srv;
	while (1)
	{
		init_fd(e);
		s->r = select(s->max + 1, &s->fd_read, &s->fd_write, NULL, NULL);
		check_fd(e);
	}
}

/*
void	display_p(t_env *e)
{
	int		i;

	i = 0;
	printf("port : %d\n", e->game->port);
	printf("width : %d\n", e->game->width);
	printf("height : %d\n", e->game->height);
	printf("max player : %d\n", e->game->mx_pl);
	printf("nb player : %d\n", e->game->nb_pl);
	printf("time : %d\n", e->game->time);
	printf("nb_team : %d\n", e->game->nb_team);
	while (i < e->game->nb_team)
	{
		printf("team %d : %s\n", i, e->game->team[i]);
		i++;
	}
}
*/

int				my_init(t_env *env)
{
	init_users(env);
	init_serv(env);
	return (0);
}

int				main(int argc, char **argv)
{
	t_env			env;

	srand(time(NULL));
	ft_bzero(&env.opt, sizeof(t_opt));
	if (get_serv_opt(&env.opt, argc, argv))
		return (1);
	my_init(&env);
	generate_map(&env, env.opt.x, env.opt.y);
	run_serv(&env);
	return (0);
}
