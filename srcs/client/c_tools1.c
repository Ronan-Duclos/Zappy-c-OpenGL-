/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_tools1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/25 16:04:27 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/19 18:36:04 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		my_exit(int sig, char *line)
{
	static int	i;

	if (sig == 0 && line != NULL)
	{
		if (ft_strcmp(line, "mort") == 0)
			i = 1;
	}
	return (i);
}

