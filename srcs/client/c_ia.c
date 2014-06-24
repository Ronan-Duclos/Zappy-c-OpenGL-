/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_ia.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/23 22:59:41 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/24 20:11:44 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>
#include <conf.h>

int			what_i_need(t_env *e, t_ia *ia);
int			i_need_to_eat(t_env *e);
int			what_i_do(t_env *e);
void		i_begin(t_env *e);
void		search_food(t_env *e);
void		search_p_to_lvlup(t_env *e);
void		search_s_to_lvlup(t_env *e);

void	choose_move(t_env *e)
{
	int		*inv;

	inv = e->user->player.ia.inv;
	if (inv[_food] < 10)
		search_food(e);
	else if (e->user->player.ia.msg != NULL)
		search_p_to_lvlup(e);
	else
		search_s_to_lvlup(e);
}

void	begin_move(t_env *e, int aw)
{
	e->user->player.acts[aw].wait = 1;
	send_inventaire(e);
	e->user->player.acts[aw].wait = 0;
	send_watch_sight(e);
}

void	my_ia(t_env *e)
{
	int				aw;
	int				ar;
	static int		i;

	aw = e->user->player.cur_awrite;
	ar = e->user->player.cur_aread;
	if (e->user->ig == 1 && e->user->player.acts[aw].time == 0 &&
		e->user->player.acts[ar].wait != 1)
	{
		if (e->user->player.ia.begin == 1)
			i_begin(e);
		else
		{
			if (i == 0)
			{
				begin_move(e, aw);
				i = 1;
			}
			else
			{
				choose_move(e);
				i = 0;
			}
		}
	}
}

void		i_begin(t_env *e)
{
	int		aw;

	aw = e->user->player.cur_awrite;
	e->user->player.acts[aw].wait = 1;
	send_fork(e);
	e->user->player.ia.begin = 0;
}

/*
int			what_i_do(t_env *e)
{
	int			need;

	need = what_i_need(e, &e->user->player.ia);
	if (need == _food)
		i_need_to_eat(e);
	return (0);
}

int			what_i_need(t_env *e, t_ia *ia)
{
	if (ia->inv[_food] < MIN_FOOD)
		return (_ia_food);
	(void)e;
	else if (ia->lvl < LVL_MAX)
	{
		if (i_have_stone(ia->inv))
		{
			if (i_can_evolve(ia->lvl))
				return (_ia_evolve);
			else
				return (_ia_player);
		}
		else
			return (_ia_stone);
	}
	else
		return (_ia_other);
	return (-1);
}

int			i_do_it(t_env *e, int act)
{
	if (act == _ia_food)
		i_need_to_eat(e);
	return (-1);
}

int		get_middle(int level)
{
	if (level == 0)
		return (0);
	return (2 * level + get_middle(level - 1));
}

int			is_in_sight(t_env *e, int type)
{
	int		i;
	int		j;

	i = -1;
	while (e->user->player.ia.view[i])
	{
		if (e->user->player.ia.view[i][type] > 0)
		{
			j = 0;
			while (i > (get_vision_nb_cell(j) - 1))
				j++;
			e->user->player.ia.destx = j - 1;
			e->user->player.ia.desty = i - get_middle(e->user->player.ia.lvl);
			return (1);
		}
		i++;
	}
	return (0);
}


void		go_to(t_env *e)
{
	t_ia		*ia;

	ia = &e->user->player.ia;
	while (ia->destx--)
		add_todo(e, send_move_forward, NULL);
	if (ia->desty < 0)
		add_todo(e, send_turn_left, NULL);
	if (ia->desty > 0)
		add_todo(e, send_turn_right, NULL);
	while (ia->desty--)
		add_todo(e, send_move_forward, NULL);
}

int			find_item(t_env *e, int type)
{
	int			nb;

	if (is_in_sight(e, type))
		go_to(e);
	else
	{
		nb = rand_int(1, 4);
		if (nb <= 2)
			add_todo(e, send_move_forward, NULL);
		else if (nb == 3)
			add_todo(e, send_turn_right, NULL);
		else if (nb == 4)
			add_todo(e, send_turn_left, NULL);
		add_todo(e, send_watch_sight, NULL);
	}
	return (0);
}

int			i_need_to_eat(t_env *e)
{
	if (e->user->player.ia.inv[_food] <  MIN_FOOD2)
	{
		find_item(e, _food);
	}
	return (1);
}
*/
