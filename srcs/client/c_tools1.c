/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_tools1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/25 16:04:27 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/17 21:25:03 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		my_exit(int sig, char *line)
{
	static int	i;

	if (sig == 0 && line != NULL)
	{
		if (ft_strcmp(line, "/quit\0") == 0)
			i = 1;
	}
	return (i);
}

void	rcv_keyboard(t_env *e)
{
	char	*line;

	get_next_line(0, &line);
	my_exit(0, line);
	tmp_to_bc(&e->user->buf_write, line, 1);
	free(line);
}

