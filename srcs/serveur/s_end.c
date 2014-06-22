/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_end.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/21 20:15:55 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/21 22:07:44 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>
#include <libft.h>

void	verify_win(t_env *e, int cs)
{
	int		i;

	i = 0;
	while (i < e->nb_team)
	{
		if (ft_strcmp(e->team[i].name, e->users[cs]->player.team) == 0)
			if (e->users[cs]->player.lvl == 8)
			{
				e->team[i].win++;
				if (e->team[i].win == 6)
					e->end = 1;
			}
		i++;
	}
}
