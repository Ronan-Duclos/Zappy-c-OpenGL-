/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_serveur_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/17 21:24:20 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/26 23:39:43 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>

int		check_word(char *str, char *str2)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && str2[i] != '\0')
	{
		if (str[i] != str2[i])
			return (-1);
		i++;
	}
	return (0);
}

void	send_serveur(t_env *e)
{
	int		i;

	bc_to_tmp(&e->user->buf_write, e->user->buf_write_tmp);
	i = ft_strlen(e->user->buf_write_tmp);
	printf("\033[32mSend : \033[0m%s", e->user->buf_write_tmp);
	send(e->user->sock, e->user->buf_write_tmp, i, 0);
	ft_bzero(e->user->buf_write_tmp, i);
}
