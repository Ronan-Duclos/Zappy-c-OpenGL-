/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_cmd_connect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 16:29:04 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/26 16:59:02 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

void		cmd_msz(char *cmd)
{
	int		i;

	printf("cmd_msz: %s\n", cmd);
	i = 3;
	i += get_next_int(&g_env->mapw, &cmd[i]);
	i += get_next_int(&g_env->maph, &cmd[i]);
	if (!g_env->sq)
		map_init();
}

void		cmd_sgt(char *cmd)
{
	int		i;

	i = 3;
	get_next_int(&g_env->time, &cmd[i]);
}

void		cmd_seg(char *cmd)
{
	int		i;

	printf("cmd_seg: %s\n", cmd);
	i = 0;
	while (cmd[i] && cmd[i] == ' ')
		i++;
}
