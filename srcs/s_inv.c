/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_inv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 15:50:27 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/08 22:01:06 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <common.h>
#include <serveur.h>

void			send_inv(t_env *env, int id)
{
	int				i;
	t_inv			*inv;
	char			*tmp;

	inv = &env->users[id]->player.inv;
	tmp_to_bc(&env->users[id]->buf_write, "{ ", 0);
	i = -1;
	while (++i < NB_STONE + 1)
	{
		tmp_to_bc(&env->users[id]->buf_write, type_to_str(i), 0);
		tmp = ft_itoa((*inv)[i]);
		tmp_to_bc(&env->users[id]->buf_write, tmp, 0);
//		free(tmp);
		if (i < NB_STONE)
			tmp_to_bc(&env->users[id]->buf_write,  ", ", 0);
	}
	tmp_to_bc(&env->users[id]->buf_write, "}", 1);
}
/*
void			send_vision(t_env *env, int id, t_inv *visible)
{
	int				i;
	int				nb;

	write_bc(env, id, "{ ", 0);
	while (visible)
	{
		i = -1;
		while (++i < NB_STONE + 1)
		{
			nb = (*visible)[i];
			while (nb--)
			{
				write_bc(env, id, type_to_str(i), 0);
				write_char_bc(env, id, ' ');
			}
		}
		visible++;
	}
}*/
