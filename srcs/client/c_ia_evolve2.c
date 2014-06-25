/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_ia_evolve2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/25 19:53:26 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/25 21:42:06 by rbernand         ###   ########.fr       */
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
		while (ia->view[0][i] < g_lvlup[ia->lvl - 1][i]
				&& ia->inv[i])
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
	if (ia->view[0][_player] + 1 >= g_lvlup[ia->lvl - 1][_player])
		return (1);
	return (0);
}

void		try_to_evolve(t_env *e, t_ia *ia)
{
	int				stat;

	stat = i_have_stone(ia);
	printf("in try to evolve : stat [%d]\n", stat);
	if (ia->msg && atoi(ia->msg) == ia->lvl)
		goto_bc(e);
	else if (stat == -1)
		find_all_stone(e, ia);
	else if (stat == 1 || stat == 2)
	{
		if (player_ok(ia))
		{
			put_all_stone(e, ia);
			add_todo(e, send_incantation, "");
		}
		else
			add_todo(e, send_broadcast, make_broadcast(ia));
	}
	else if (stat == 0)
		add_todo(e, send_incantation, NULL);

}
