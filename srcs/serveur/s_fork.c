/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_fork.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/16 21:11:49 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/16 21:11:49 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>
#include <libft.h>

void	my_fork(t_env *e, int cs)
{
	int		i;

	i = -1;
	while (e->opt.name[++i] != NULL)
		if (ft_strcmp(e->users[cs]->player.team, e->team[i].name) == 0)
		{
			if (e->team[i].member < ((e->srv.max_fd - 4) / 2))
				tmp_to_bc(&e->users[cs]->buf_write, "ok", 1);
			else
				tmp_to_bc(&e->users[cs]->buf_write, "ko", 1);
		}

}
