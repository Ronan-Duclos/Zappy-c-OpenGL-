/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_less_hp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/18 22:03:06 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/18 22:03:32 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>
#include <math.h>

int		less_hp(t_env *e, int cs)
{
	double	now;
	double	less;
	int		i;

	i = 0;
	now = ft_usec_time();
	less = now - e->users[cs]->time;
	while (less > (double)(126 * 1000000) / e->opt.time)
	{
		less = fmod(less, (double)((126 * 1000000) / e->opt.time));
		e->users[cs]->player.inv[_food] = e->users[cs]->player.inv[_food] - 1;
		e->users[cs]->time = now - less;
		i++;
		if (e->users[cs]->player.inv[_food] == -1)
		{
			tmp_to_bc(&e->users[cs]->buf_write, "DEAD", 1);
			return (-1);
		}
	}
	return (0);
}
