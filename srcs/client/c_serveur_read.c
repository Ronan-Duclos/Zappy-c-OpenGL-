/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_serveur_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/17 21:25:21 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/17 21:29:07 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>

void	ask_to_play(t_env *e)
{
	tmp_to_bc(&e->user->buf_write, e->me.name, 1);
	printf("name: %s\n", e->me.name);
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
