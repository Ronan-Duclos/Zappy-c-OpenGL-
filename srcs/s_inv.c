/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_inv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 15:50:27 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/06 18:48:16 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>
#include <serveur.h>

void			send_inv(t_env *env, int id)
{
	int				i;
	t_inv			*inv;

	inv = &env->users[id]->player.inv;
	write_char_bc(env, id, '{', 0);
	i = -1;
	while (++i < NB_STONE + 1)
	{
		write_bc(env, id, type_tos_tr(i), 0);
		write_char_bc(env ,id, ' ');
		write_nbr_bc(env, id, inv[i], 0);
		if (i < NB_STONE)
			write_char_bc(env ,id, ", ");
	}
	write_bc(env, id, "}", 1);
}

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
}
