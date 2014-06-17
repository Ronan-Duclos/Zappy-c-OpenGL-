/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_serveur_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/17 21:24:20 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/17 22:40:25 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>

void	rcv_keyboard(t_env *e)
{
	char	*line;

	get_next_line(0, &line);
	my_exit(0, line);
	tmp_to_bc(&e->user->buf_write, line, 1);
	free(line);
}

void	send_serveur(t_env *e)
{
	int		i;

	bc_to_tmp(&e->user->buf_write, e->user->buf_write_tmp);
	i = ft_strlen(e->user->buf_write_tmp);
	printf("Send : %s", e->user->buf_write_tmp);
	send(e->user->sock, e->user->buf_write_tmp, i, 0);
	ft_bzero(e->user->buf_write_tmp, i);
}
