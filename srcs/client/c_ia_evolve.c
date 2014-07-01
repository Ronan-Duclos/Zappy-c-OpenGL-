/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_ia_evolve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/25 19:53:26 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/26 23:56:56 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <global.h>

void		put_all_stone(t_env *e, t_ia *ia)
{
	int 			i;

	i = 0;
	while (i < NB_STONE)
	{
		while (ia->view[0][i] < g_lvlup[ia->lvl - 1][i] && ia->inv[i])
		{
			ia->view[0][i]++;
			ia->inv[i]--;
			add_todo(e, send_drop_item, type_to_str(i));
		}
		i++;
	}
}

void		find_all_stone(t_env *e, t_ia *ia)
{
	int			i;

	i = 0;
	while (++i < NB_STONE)
	{
		if (g_lvlup[ia->lvl - 1][i] > ia->inv[i])
		{
			find_item(e, i);
			break ;
		}
	}
}

int			player_ok(t_ia *ia)
{
//	printf("PLAYER OK : lvl [%d] nb have : [%d] nb need :[%d]\n", ia->lvl, ia->view[0][_player] + 1,
//		   g_lvlup[ia->lvl - 1][_player]);
	if ((ia->view[0][_player] + 1) >= g_lvlup[ia->lvl - 1][_player])
		return (1);
	return (0);
}

void		try_to_evolve(t_env *e, t_ia *ia)
{
	int				stat;
	static int		i;

	stat = i_have_stone(ia);
//	printf("in try to evolve : stat [%d]\n", stat);
	if (ia->msg && atoi(ia->msg) == ia->lvl)
		goto_bc(e);
	else if (stat == -1)
		find_all_stone(e, ia);
	else
	{
		if (player_ok(ia))
		{
			if (stat == 1)
				put_all_stone(e, ia);
			add_todo(e, send_incantation, NULL);
			i = 0;
		}
		else
		{
			if (i == 0)
			{
				add_todo(e, send_fork, NULL);
				i = 1;
			}
			else
			{
				if (stat == 1)
					put_all_stone(e, ia);
				add_todo(e, send_broadcast, make_broadcast(ia));
			}
		}
	}
}
