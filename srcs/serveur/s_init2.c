/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_init2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 18:28:25 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/26 18:28:51 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>
#include <libft.h>

void	add_start_cal(t_env *e, int cs, int team)
{
	int				*aw;
	t_actions		*act;

	aw = &e->users[cs]->player.cur_awrite;
	act = &e->users[cs]->player.acts[*aw];
	act->cmd = ft_itoa(e->team[team].member);
	act->answer = NULL;
	act->time = e->users[cs]->time;
	act->start = 0;
	act->fct_cmd = send_start;
	act->fct_gfx = NULL;
	*aw = (*aw + 1) % 10;
}

void	init_egg(t_env *e, int cs, t_egg *egg, int team)
{
	printf("\033[35mClient is an egg\033[0m : %d\n", cs);
	e->users[cs]->player.x = egg->x;
	e->users[cs]->player.y = egg->y;
	e->users[cs]->player.inv[_food] = NB_START_FOOD;
	e->users[cs]->time = egg->t_eclos;
	gfx_send_egg(e, egg, gfx_ebo);
	del_egg(&e->team[team]);
}

void	init_player(t_env *e, int cs, int team)
{
	double			time;
	t_egg			*egg;

	e->users[cs]->player.direc = rand() % 4;
	e->users[cs]->player.lvl = 1;
	e->users[cs]->player.lvlup = 0;
	e->users[cs]->player.lvlup_good = 0;
	time = ft_usec_time();
	if ((egg = e->team[team].eggs) == NULL)
	{
		printf("\033[36mClient is a player\033[0m : %d\n", cs);
		e->users[cs]->player.x = rand() % e->opt.x;
		e->users[cs]->player.y = rand() % e->opt.y;
		e->users[cs]->player.inv[_food] = NB_START_FOOD;
		e->users[cs]->time = time;
	}
	else
		init_egg(e, cs, egg, team);
	add_start_cal(e, cs, team);
}