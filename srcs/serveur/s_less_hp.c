/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_less_hp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/18 22:03:06 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/21 18:25:07 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>
#include <math.h>

int		lost_food(int sig)
{
	static int	food;

	if (sig == 1)
		food++;
	else if (sig == -1)
		food = 0;
	else if (sig == 0)
		return (food);
	return (0);
}

void	generate_food(t_env *e)
{
	int		nb;
	int		x;
	int		y;
	double	now;

	now = ft_usec_time();
	if (now >= e->repop)
	{
		nb = lost_food(0);
		while (nb != 0)
		{
			x = rand() % e->opt.x;
			y = rand() % e->opt.y;
			e->map[x][y].ground[_food]++;
			nb--;
		}
		lost_food(-1);
		e->repop = ft_usec_time() + ((126 * 1000000) / e->opt.time);
	}
}

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
		lost_food(1);
		i++;
		if (e->users[cs]->player.inv[_food] == -1)
		{
			gfx_send_npc(e, cs, gfx_pdi); //added gfx_msg
			tmp_to_bc(&e->users[cs]->buf_write, "DEAD", 1);
			return (-1);
		}
	}
	return (0);
}
