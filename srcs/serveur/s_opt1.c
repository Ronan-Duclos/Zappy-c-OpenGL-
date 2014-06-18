/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_opt1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/30 14:58:39 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/18 21:36:28 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <serveur.h>

int				check_name(int n, char **name)
{
	int			i;
	int			j;

	i = -1;
	while (name[++i])
	{
		if (ft_strequ(name[i], "GRAPHIC"))
			return (0);
		j = -1;
		while (name[++j])
		{
			if (i != j && ft_strequ(name[i], name[j]))
				return (0);
		}
	}
	return (n);
}

int				get_name(char **argv, t_opt *opt)
{
	int		n;
	int		i;

	n = 0;
	while (argv[n + 1] && argv[n + 1][0] != '-')
		n++;
	opt->name = (char **)malloc((n + 1) * sizeof(char *));
	i = -1;
	while (++i < n)
		opt->name[i] = ft_strdup(argv[i + 1]);
	opt->name[n] = NULL;
	return (check_name(n, opt->name));
}

int				check_opt(t_opt *opt)
{
	if (opt->port <= 0)
		return (printf("Invalid argument -p : %d\n", opt->port));
	else if (opt->x <= 0)
		return (printf("Invalid argument -x : %d\n", opt->x));
	else if (opt->y <= 0)
		return (printf("Invalid argument -y : %d\n", opt->y));
	else if (opt->client <= 0)
		return (printf("Invalid argument -c : %d\n", opt->client));
	else if (opt->time <= 0)
		return (printf("Invalid argument -t: %d\n", opt->time));
	else if (opt->name == NULL || (opt->name && opt->name[0] == NULL))
		return (printf("Invalid argument -n : <team> [<team>] ...\n"));
	return (0);
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

int				get_serv_opt(t_opt *opt, int argc, char **argv)
{
	int						i;
	int						c;
	static t_fct_opt		fct[] = {

	get_port, get_x, get_y, get_name, get_client, get_time};
	i = 1;
	while (argv[i])
		if (argv[i][0] == '-')
		{
			if (argv[i][1] && (c = get_arg(argv[i][1])) != -1 && !argv[i][2])
				i += fct[c](argv + i, opt) + 1;
			else
				return (printf("Illegal argument : %s\n", argv[i]));
		}
		else if (i < argc)
			return (printf("Invalid option : %s\n", argv[i]));
		else
			break ;
	return (check_opt(opt));
}
