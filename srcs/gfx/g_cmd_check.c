/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_cmd_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/18 17:16:37 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/18 21:57:12 by caupetit         ###   ########.fr       */
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
		{"ppo", &cmd_ppo}
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
			printf("UNKNOWN CMD %d, %s\n", i, tab[i]);
		i++;
	}
	printf("end_cmd_check state: %d\n", ipv->state);
	dtab_del(tab);
}
