/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_end.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/21 20:15:55 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/23 14:51:06 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>
#include <libft.h>

void	verify_win(t_env *e, int cs)
{
	int		i;

	i = -1;
	if (e->msg_end == 1)
	{
		e->end = 1;
		return ;
	}
	while (++i < e->nb_team)
	{
		if (ft_strcmp(e->team[i].name, e->users[cs]->player.team) == 0 &&
			e->users[cs]->player.lvl == 8)
		{
			e->team[i].win++;
			if (e->team[i].win == 6)
			{
				e->msg_end = 1;
				
				// add cmd de fin de jeux serveur.
			}
		}
	}
}
