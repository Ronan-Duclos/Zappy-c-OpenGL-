/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_less_hp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/18 22:03:06 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/23 17:37:52 by rbernand         ###   ########.fr       */
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

	printf("\033[33mIN FOOD REGENERATE\033[0m\n");
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
			gfx_send_map(e, x, y, gfx_bct);
		}
		lost_food(-1);
		e->repop = ft_usec_time() + ((126 * 1000000) / e->opt.time);
	}
}

void		less_hp_eggs(t_env *e)
{
	int			i;
	t_egg		*egg;
	double		now;
	double		dec;

	now = ft_usec_time();
	i = -1;
	while (e->opt.name[++i])
	{
		egg = e->team[i].eggs;
		while (egg)
		{
			dec = now - egg->t_last;
			if (dec > 0 && (dec / ((double)(126 * 1000000) / e->opt.time)) > 1)
			{
				printf("%d\n", egg->food);
				egg->t_last = now;
				egg->food = egg->food - dec / (double)(126 * 1000000) / e->opt.time;
			}
			if (egg->food <= 0)
			{
				del_egg(&e->team[i]);
				e->team[i].member--;
			}
			egg = egg->next;
		}
	}
}

int		less_hp(t_env *e, int cs)
{
	double	now;
	double	less;

	now = ft_usec_time();
	less = now - e->users[cs]->time;
	while (less > (double)(126 * 1000000) / e->opt.time)
	{
		less = fmod(less, (double)((126 * 1000000) / e->opt.time));
		e->users[cs]->player.inv[_food] = e->users[cs]->player.inv[_food] - 1;
		e->users[cs]->time = now - less;
		lost_food(1);
		printf("%d\n", e->users[cs]->player.inv[_food]);
		if (e->users[cs]->player.inv[_food] < 0)
		{
			tmp_to_bc(&e->users[cs]->buf_write, "mort", 1);
//			gfx_send_npc(e, cs, gfx_pdi); a voir deja mis a la deconnection du client
			return (-1);
		}
	}
	return (0);
}
