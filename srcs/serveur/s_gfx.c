/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_gfx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 16:54:11 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/26 23:48:36 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "serveur.h"
#include "libft.h"

void		gfx_msz(t_env *e, int cs)
{
	char	buf[BUF_SIZE];

	ft_bzero(buf, BUF_SIZE);
	sprintf(buf, "msz %d %d", e->opt.x, e->opt.y);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

void		gfx_sgt(t_env *e, int cs)
{
	char	buf[BUF_SIZE];

	ft_bzero(buf, BUF_SIZE);
	sprintf(buf, "sgt %d", e->opt.time);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

void		gfx_seg(t_env *e, int cs, int clt)
{
	char	buf[BUF_SIZE];

	ft_bzero(buf, BUF_SIZE);
	sprintf(buf, "seg %s", e->users[clt]->player.team);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

void		gfx_tna(t_env *e, int cs)
{
	char	buf[BUF_SIZE];
	int		i;

	i = -1;
	while (e->opt.name[++i])
	{
		bzero(buf, BUF_SIZE);
		sprintf(buf, "tna %s", e->opt.name[i]);
		tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
	}
}
