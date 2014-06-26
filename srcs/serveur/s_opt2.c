/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_opt2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/18 21:31:46 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/26 12:08:33 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <serveur.h>

int				get_verbose(char **argv, t_opt *opt)
{
	(void)argv;
	opt->v = 1;
	return (1);
}

int				get_port(char **argv, t_opt *opt)
{
	opt->port = ft_atoi(argv[1]);
	return (1);
}

int				get_x(char **argv, t_opt *opt)
{
	opt->x = ft_atoi(argv[1]);
	return (1);
}

int				get_y(char **argv, t_opt *opt)
{
	opt->y = ft_atoi(argv[1]);
	return (1);
}

int				get_client(char **argv, t_opt *opt)
{
	opt->client = ft_atoi(argv[1]);
	return (1);
}

int				get_time(char **argv, t_opt *opt)
{
	opt->time = ft_atoi(argv[1]);
	return (1);
}
