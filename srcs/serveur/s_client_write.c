/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/25 16:12:43 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/20 23:14:07 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "libft.h"

void	client_write(t_env *e, int cs)
{
	int		i;

	bc_to_tmp(&e->users[cs]->buf_write, e->users[cs]->buf_write_tmp);
	i = ft_strlen(e->users[cs]->buf_write_tmp);
	printf("Send to %d : %s", cs, e->users[cs]->buf_write_tmp);
	send(cs, e->users[cs]->buf_write_tmp, i, 0);
	e->users[cs]->buf_write_tmp[0] = '\0';
}
