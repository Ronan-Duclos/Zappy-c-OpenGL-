/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_gfx_egg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 17:19:00 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/26 17:47:27 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "serveur.h"
#include "libft.h"

void		gfx_enw(t_env *e, int cs, t_egg *egg)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	sprintf(buf, "enw #%d #%d %d %d", egg->id, egg->cs,
			e->users[egg->cs]->player.x,
			e->users[egg->cs]->player.y);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

void		gfx_eht(t_env *e, int cs, t_egg *egg)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	sprintf(buf, "eht #%d", egg->id);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

void		gfx_ebo(t_env *e, int cs, t_egg *egg)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	sprintf(buf, "ebo #%d", egg->id);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

void		gfx_edi(t_env *e, int cs, t_egg *egg)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	sprintf(buf, "edi #%d", egg->id);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}
