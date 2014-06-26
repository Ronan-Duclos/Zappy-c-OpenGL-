/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_gfx_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 14:18:00 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/26 17:46:54 by caupetit         ###   ########.fr       */
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
	{"smg", gcmd_smg},
	{"sgt", gcmd_sgt}
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

void			gfx_cmd_check(t_env *e, int cs, char *buf)
{
	char	**tab;
	t_gcmd	*cmd;
	int		i;
	int		j;

	i = 0;
	cmd = gfx_cmds_get();
	tab = ft_strsplit(buf, '\n');
	while (tab[i])
	{
		j = 0;
		while (j < GCMD_NB && strncmp(tab[i], cmd[j].cmd, 3))
			j++;
		if (j < GCMD_NB)
			cmd[j].fu(e, cs, &tab[i][3]);
		else
			printf("UNKNOWN CMD %d, %s\n", i, tab[i]);
		i++;
	}
	ft_tabdel(&tab);
}
