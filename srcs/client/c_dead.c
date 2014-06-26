/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_dead.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 23:32:19 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/26 23:32:20 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>

int		death_clt(t_env *e)
{
	if (ft_strcmp(e->user->buf_read_tmp, "mort\n") == 0)
	{
		printf("You are dead\n");
		close(e->user->sock);
		my_exit(0, "mort");
		return (1);
	}
	return (0);
}
