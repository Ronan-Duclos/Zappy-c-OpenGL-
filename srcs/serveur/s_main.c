/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/30 12:19:56 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/19 22:36:00 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>
#include <libft.h>
#include <serveur.h>
#include <math.h>
#include <stdio.h>

void			run_serv(t_env *e)
{
	t_srv			*s;
	struct timeval	out;

	s = &e->srv;
	out.tv_usec = 0;
	out.tv_sec = 0;
	while (1)
	{
		init_fd(e);
		s->r = select(s->max + 1, &s->fd_read, &s->fd_write, NULL, &out);
		check_fd(e);
	}
}

int				my_init(t_env *e)
{
	init_users(e);
	init_serv(e);
	init_team(e);
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
	generate_map(&env);
	run_serv(&env);
	return (0);
}
