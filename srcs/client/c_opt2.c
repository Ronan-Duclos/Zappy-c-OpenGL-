/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_opt2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 19:59:21 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/27 00:03:18 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>

int				get_port(char **argv, t_opt *opt)
{
	opt->port = ft_atoi(argv[1]);
	return (1);
}

int				get_name(char **argv, t_opt *opt)
{
	opt->name = ft_strdup(argv[1]);
	return (1);
}

int				get_verbose(char **argv, t_opt *opt)
{
	(void)argv;
	opt->v = 1;
	return (1);
}
