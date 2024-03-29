/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_cmd_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/18 17:16:37 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/26 16:46:22 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "libft.h"

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

static void		cmds_get(char ***tab, char *buf)
{
	static char	tmp[BUF_SIZE];
	char		tmp2[BUF_SIZE];
	char		*tmp3;

	bzero(tmp2, BUF_SIZE);
	if (*tmp)
		strcpy(tmp2, tmp);
	bzero(tmp, BUF_SIZE);
	if (buf[strlen(buf) - 1] != '\n' && (tmp3 = strrchr(buf, '\n')))
	{
		strcpy(tmp, tmp3 + 1);
		tmp3 = '\0';
	}
	*tab = ft_strsplit(buf, '\n');
	if (*tmp2)
	{
		strcpy(&tmp2[strlen(tmp2)], *tab[0]);
		tmp3 = strdup(tmp2);
		free(*tab[0]);
		*tab[0] = tmp3;
	}
}

static t_cmd	*cmds_tab_get(void)
{
	static t_cmd	cmd[CMDS_NB] =

	{
	{"pnw", &cmd_pnw},
	{"bct", &cmd_bct},
	{"ppo", &cmd_ppo},
	{"pin", &cmd_pin},
	{"plv", &cmd_plv},
	{"pgt", &cmd_pgt},
	{"pdr", &cmd_pdr},
	{"pdi", &cmd_pdi},
	{"sgt", &cmd_sgt},
	{"pfk", &cmd_pfk},
	{"pic", &cmd_pic},
	{"pie", &cmd_pie},
	{"seg", &cmd_seg},
	{"enw", &cmd_enw},
	{"eht", &cmd_eht},
	{"ebo", &cmd_ebo},
	{"edi", &cmd_edi},
	{"pcb", &cmd_pcb}
	};
	return (cmd);
}

void			cmd_check(t_ipv *ipv, char *buf)
{
	char	**tab;
	t_cmd	*cmd;
	int		i;
	int		j;

	i = 0;
	cmd = cmds_tab_get();
	cmds_get(&tab, buf);
	if (ipv->state == _connect)
		cmd_connect(ipv, tab, &i);
	while (tab[i] && ipv->state != _connect)
	{
		j = 0;
		while (j < CMDS_NB && strncmp(tab[i], cmd[j].cmd, 3))
			j++;
		if (j < CMDS_NB)
			cmd[j].fu(&tab[i][3]);
		else
			printf("UNKNOWN CMD tab[%d]: %s\n", i, tab[i]);
		i++;
	}
	dtab_del(tab);
}
