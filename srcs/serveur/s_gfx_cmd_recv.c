/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_gfx_cmd_recv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 17:43:17 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/26 17:45:11 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "libft.h"

void			gcmd_pin(t_env *e, int cs, char *cmd)
{
	int		i;
	int		npc;

	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	i += get_next_int(&npc, &cmd[i]);
	if (npc >= e->srv.max_fd || !e->users[npc]->ig)
		return ;
	gfx_pin(e, cs, npc);
}

void			gcmd_plv(t_env *e, int cs, char *cmd)
{
	int		i;
	int		npc;

	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '#'))
		i++;
	i += get_next_int(&npc, &cmd[i]);
	if (npc >= e->srv.max_fd || !e->users[npc]->ig)
		return ;
	gfx_plv(e, cs, npc);
}

void			gcmd_smg(t_env *e, int cs, char *msg)
{
	int		i;

	(void)cs;
	i = 0;
	while (msg[i] && (msg[i] == ' ' || msg[i] == '#'))
		i++;
	if (!strncmp(&msg[i], "GO", 3))
		gfx_end_init(e);
}

void			gcmd_sgt(t_env *e, int cs, char *cmd)
{
	(void)cmd;
	gfx_sgt(e, cs);
}
