/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_gfx_npc_action.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 17:37:35 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/27 00:07:42 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "libft.h"

void		gfx_pfk(t_env *e, int cs, int clt)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	sprintf(buf, "pfk #%d", clt);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

void		gfx_pic(t_env *e, int cs, int clt)
{
	t_user	*tmp;
	char	buf[BUF_SIZE];
	int		i;
	int		lvl;

	bzero(buf, BUF_SIZE);
	i = 0;
	tmp = e->map[e->users[clt]->player.y][e->users[clt]->player.x].player;
	lvl = tmp->player.lvl;
	i += sprintf(buf, "pic %d %d %d", e->users[clt]->player.x,
				e->users[clt]->player.y,
				tmp->player.lvl);
	while (tmp)
	{
		if (tmp->player.lvl == lvl)
			i += sprintf(&buf[i], " #%d", tmp->sock);
		tmp = tmp->next;
	}
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

void		gfx_pie(t_env *e, int cs, int clt, int succes)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	if (succes != 1)
		succes = 0;
	sprintf(buf, "pie %d %d %d", e->users[clt]->player.x,
			e->users[clt]->player.y, succes);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

void		gfx_pgt(t_env *e, int cs, int clt, int itm)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	sprintf(buf, "pgt #%d %d", clt, itm);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}

void		gfx_pdr(t_env *e, int cs, int clt, int itm)
{
	char	buf[BUF_SIZE];

	bzero(buf, BUF_SIZE);
	sprintf(buf, "pdr #%d %d", clt, itm);
	tmp_to_bc(&e->users[cs]->buf_write, buf, 1);
}
