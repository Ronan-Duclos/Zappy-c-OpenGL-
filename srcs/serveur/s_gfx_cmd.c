/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_gfx_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 14:18:00 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/20 11:50:11 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "libft.h"

static t_gcmd	*gfx_cmds_get(void)
{
	static t_gcmd	cmd[GCMD_NB] =

	{
		{"pin", gcmd_pin},
		{"plv", gcmd_plv},
		{"smg", gcmd_smg}
	};
	return (cmd);
}

int				get_next_int(int *nb, char *s)
{
	int		i;
	int		tmp;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	*nb = ft_atoi(&s[i]);
	tmp = *nb;
	i++;
	while (tmp / 10)
	{
		tmp /= 10;
		i++;
	}
	return (i);
}

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

void			gfx_cmd_check(t_env *e, int cs, char *buf)
{
	char	**tab;
	t_gcmd	*cmd;
	int		i;
	int		j;

	i = 0;
	printf("gfx_cmd_check: buf: %s\n", buf);
	cmd = gfx_cmds_get();
	tab = ft_strsplit(buf, '\n');
	while (tab[i])
	{
		printf("tab[%d]: %s\n", i, tab[i]);
		j = 0;
		while (j < GCMD_NB && strncmp(tab[i], cmd[j].cmd, 3))
			j++;
		if (j < GCMD_NB)
			cmd[j].fu(e, cs, &tab[i][3]);
		else
			printf("UNKNOWN CMD %d, %s\n", i, tab[i]);
		i++;
	}
	printf("end gfx_cmd_check \n");
	ft_tabdel(&tab);
}
