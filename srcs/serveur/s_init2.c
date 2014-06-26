/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_init2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 18:28:25 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/26 18:28:51 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>

void	init_fd(t_env *e)
{
	int		i;

	i = 0;
	FD_ZERO(&e->srv.fd_read);
	FD_ZERO(&e->srv.fd_write);
	e->srv.max = 3;
	while (i < (e->srv.max_fd))
	{
		if (e->users[i]->type != FD_FREE)
		{
			if (e->users[i]->type == FD_CLT && e->users[i]->ig == 1
				&& !e->users[i]->gfx.gfx)
				check_actions(e, i);
			FD_SET(i, &e->srv.fd_read);
			if (verify_bsn(&e->users[i]->buf_write) == 1)
				FD_SET(i, &e->srv.fd_write);
			if (e->srv.max < i)
				e->srv.max = i;
		}
		i++;
	}
}

void	init_serv(t_env *e)
{
	int		i;

	e->srv.glst = NULL;
	i = init_sock(e->opt.port, e);
	e->repop = ft_usec_time() + ((126 * 1000000) / e->opt.time);
	e->srv.time = 2000000000000;
	e->users[i]->fct_read = create_clt;
	e->users[i]->fct_write = client_write;
	e->users[i]->type = FD_SRV;
	e->end = 0;
}
