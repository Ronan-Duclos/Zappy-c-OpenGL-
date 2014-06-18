/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_connect_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/16 21:11:19 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/18 21:59:53 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>
#include "libft.h"

void	connect_nbr(t_env *e, int cs)
{
	int		i;
	char	*tmp;

	i = -1;
	while (e->opt.name[++i] != NULL)
		if (ft_strcmp(e->team[i].name, e->users[cs]->player.team) == 0)
		{
			tmp = ft_itoa(e->team[i].member);
			tmp_to_bc(&e->users[cs]->buf_write, tmp, 1);
		}
}
