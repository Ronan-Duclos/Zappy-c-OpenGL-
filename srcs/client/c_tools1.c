/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_tools1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/25 16:04:27 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/11 15:57:38 by caupetit         ###   ########.fr       */
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

void	send_serveur(t_env *e)
{
	int		i;

	bc_to_tmp(&e->user->buf_write, e->user->buf_write_tmp);
	i = ft_strlen(e->user->buf_write_tmp);
	printf("Send : %s", e->user->buf_write_tmp);
	send(e->user->sock, e->user->buf_write_tmp, i, 0);
	ft_bzero(e->user->buf_write_tmp, i);
}

void	ask_to_play(t_env *e)
{
	tmp_to_bc(&e->user->buf_write, e->me.name, 1);
	printf("name: %s\n", e->me.name);//
	e->user->ig = 1;
}

void	make_cmd(t_env *e)
{
	if (e->user->ig == 0)
		ask_to_play(e);
}

void	rcv_serveur(t_env *e)
{
	int		r;

	r = recv(e->user->sock, e->user->buf_read_tmp, BC_SIZE, 0);
	if (r <= 0)
	{
		close(e->user->sock);
		exit(0);
	}
	e->user->buf_read_tmp[r] = '\0';
	tmp_to_bc(&e->user->buf_read, e->user->buf_read_tmp, 0);
	e->user->buf_read_tmp[0] = '\0';
	if (verify_bsn(&e->user->buf_read) == 1)
	{
		bc_to_tmp(&e->user->buf_read, e->user->buf_read_tmp);
		printf("Receive : %s", e->user->buf_read_tmp);
		make_cmd(e);
		r = ft_strlen(e->user->buf_read_tmp);
		ft_bzero(e->user->buf_read_tmp, r);
	}
}
