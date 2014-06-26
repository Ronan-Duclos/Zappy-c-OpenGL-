/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_inv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 15:50:27 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/26 12:53:44 by rbernand         ###   ########.fr       */
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
//	char			*tmp;
	char			buf[50];

	inv = &env->users[id]->player.inv;
	char_to_bc(&env->users[id]->buf_write, '{');
	i = -1;
	while (++i < NB_STONE + 1)
	{
		bzero(buf, 50);
		sprintf(buf, "%s %d", type_to_str(i), (*inv)[i]);
		tmp_to_bc(&env->users[id]->buf_write, buf, 0);
/*		char_to_bc(&env->users[id]->buf_write, ' ');
		tmp = ft_itoa((*inv)[i]);
		tmp_to_bc(&env->users[id]->buf_write, tmp, 0);
		free(tmp);*/
		if (i < NB_STONE)
			tmp_to_bc(&env->users[id]->buf_write, ", ", 0);
	}
	tmp_to_bc(&env->users[id]->buf_write, "}", 1);
}
