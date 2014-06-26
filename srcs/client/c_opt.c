/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_opt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/30 15:29:22 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/26 12:05:20 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <client.h>
#include <sys/socket.h>
#include <netdb.h>


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

int				get_host(char **argv, t_opt *opt)
{
	opt->host = ft_strdup(argv[1]);
	return (1);
}

int				get_arg(char to_test)
{
	int				c;
	static char		valid[] = OPT;

	c = -1;
	while (valid[++c])
		if (valid[c] == to_test)
			return (c);
	return (-1);
}

int				check_opt(t_opt *opt)
{
	if (opt->port <= 0)
		return (printf("Invalid argument -p : %d\n", opt->port));
	else if (opt->name == NULL)
		return (printf("Invalid argument -n : <team>\n"));
	if (opt->host == NULL || strcmp(opt->host, "localhost") == 0)
		opt->host = strdup("127.0.0.1");
	return (0);
}

int				get_clt_opt(t_opt *opt, int argc, char **argv)
{
	int						i;
	int						c;
	static t_fct_opt		fct[] = {

	get_name, get_verbose, get_port, get_host};
	i = 1;
	ft_bzero(opt, sizeof(opt));
	opt->v = 0;
	while (--argc && argv[i])
	{
		if (argv[i][0] == '-')
		{
			if (argv[i][1] && (c = get_arg(argv[i][1])) != -1 && !argv[i][2])
				i += fct[c](argv + i, opt);
			else
				return (printf("Illegal argument : %s\n", argv[i]));
		}
		else
			i++;
	}
	return (check_opt(opt));
}

void			put_opt(t_opt *opt)
{
	printf("port : %d\n", opt->port);
	printf("name : %s\n", opt->name);
	printf("host : %s\n", opt->host);
}
