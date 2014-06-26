/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_gfx_npc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 17:39:51 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/26 17:49:47 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "libft.h"

void		gfx_plv(t_env *e, int cs, int clt)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	sprintf(buf, "plv #%d %d", clt, e->users[clt]->player.lvl);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

void		gfx_pdi(t_env *e, int cs, int clt)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	sprintf(buf, "pdi #%d", clt);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

void		gfx_pcb(t_env *e, int cs, int clt, char *msg)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	sprintf(buf, "pcb #%d %s", clt, msg);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

void		gfx_pin(t_env *e, int cs, int clt)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	sprintf(buf, "pin #%d %d %d %d %d %d %d %d %d %d", clt,
			e->users[clt]->player.x,
			e->users[clt]->player.y,
			e->users[clt]->player.inv[_food],
			e->users[clt]->player.inv[_linemate],
			e->users[clt]->player.inv[_deraumere],
			e->users[clt]->player.inv[_sibur],
			e->users[clt]->player.inv[_mendiane],
			e->users[clt]->player.inv[_phiras],
			e->users[clt]->player.inv[_thystame]);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}
