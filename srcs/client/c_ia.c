/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_ia.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/25 22:53:51 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/27 09:05:19 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>
#include <conf.h>

int			what_i_need(t_env *e, t_ia *ia);
int			i_need_to_eat(t_env *e);
int			what_i_do(t_env *e);
int			i_begin(t_env *e);
int			find_item(t_env *e, int type);
void		my_ia(t_env *e);

void	try_ia(t_env *e)
{
	int				aw;
	int				ar;

	aw = e->user->player.cur_awrite;
	ar = e->user->player.cur_aread;
	if (e->user->ig == 1 && e->user->player.acts[aw].time == 0)
	{
		if (e->user->player.ia.lvlup == 1)
			;
		else if (e->user->player.ia.todo != NULL)
			todo_to_cal(e);
		else if (ar == aw)
			my_ia(e);
	}
}

void	my_ia(t_env *e)
{

	static int		i = -1;

	if (e->user->player.ia.recolt == 1 && e->user->player.ia.view[0][_food] == 0)
	{
		add_todo(e, send_inventaire, NULL);
		add_todo(e, send_watch_sight, NULL);
	}
	if (i == -1)
	{
		add_todo(e, send_inventaire, NULL);
		add_todo(e, send_watch_sight, NULL);
		i = 1;
	}
	else
	{
		printf("in my ia : [%d]\n", i);
		i = what_i_do(e);
	}
	todo_to_cal(e);
}

int			i_begin(t_env *e)
{
	send_inventaire(e);
	send_watch_sight(e);
	send_fork(e);
	return (0);
}

int			check_end(t_ia *ia, int need)
{
	if (ia->inv[_food] < MIN_FOOD)
		return (-1);
	if (need == _ia_food)
	{
		if (ia->inv[_food] > MIN_FOOD2)
			return (_ia_evolve);
		else
			return (_ia_food);
	}
	else if (need == _ia_evolve)
		return (-1);
	return (need);
}

int			what_i_do(t_env *e)
{
	int				need;
	static int		last_lvl;
	static int		last = -1;

	printf("in what i do : last [%d]\n", last);
	if (last_lvl != e->user->player.ia.lvl)
	{
		last_lvl = e->user->player.ia.lvl;
		if (last_lvl == 2)
			(void)e;
//			add_todo(e, send_fork, NULL);
		return (-1);
	}
	if (last == -1)
		need = what_i_need(e, &e->user->player.ia);
	else
		need = last;
	printf("in what i do : last2 [%d]\n", need);
	if (need == _ia_food)
		find_item(e, _food);
	else if (need == _ia_evolve)
		try_to_evolve(e, &e->user->player.ia);
	else
		printf("in what i do : lastPO [%d]\n", last);
	printf("in what i do : last3 [%d]\n", last);
	last = check_end(&e->user->player.ia, need);
	return (last);
}

int			what_i_need(t_env *e, t_ia *ia)
{
	static int		last;

	if (ia->inv[_food] > MIN_FOOD2)
	{
		last = 0;
		if (ia->recolt == 1)
			ia->recolt = 0;
	}
	if (last == -1 && ia->inv[_food] < MIN_FOOD2)
		return (_ia_food);
	else if (ia->inv[_food] < MIN_FOOD)
	{
		ia->recolt = 1;
		last = -1;
		return (_ia_food);
	}
	else
		return (_ia_evolve);
	(void)e;
/*	else if (ia->lvl < LVL_MAX)
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
		return (_ia_other);*/
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
	int		max;

	i = -1;
	if (!e->user->player.ia.view)
		return (0);
	max = get_vision_nb_cell(e->user->player.ia.lvl);
	while (++i < max)
	{
		if (e->user->player.ia.view[i][type] > 0)
		{
			j = 0;
			while (i > (get_vision_nb_cell(j) - 1))
			{
				j++;
			}
			e->user->player.ia.quantity = e->user->player.ia.view[i][type];
			e->user->player.ia.destx = j;
			e->user->player.ia.desty = j > 0 ? i - get_middle(e->user->player.ia.lvl) : 0;
			return (1);
		}
	}
	return (0);
}


void		go_to(t_env *e)
{
	t_ia		*ia;

	ia = &e->user->player.ia;
//	printf("in go to \n");
	while (ia->destx > 0)
	{
//	printf("in go to move forward\n");
		add_todo(e, send_move_forward, NULL);
		ia->destx = ia->destx - 1;
	}
	if (ia->desty < 0)
	{
		add_todo(e, send_turn_left, NULL);
//	printf("in go to turn elft\n");
		ia->desty = -ia->desty;
	}
	else if (ia->desty > 0)
		add_todo(e, send_turn_right, NULL);
	while (ia->desty > 0)
	{
//		printf("in go to | move y\n");
		add_todo(e, send_move_forward, NULL);
		ia->desty = ia->desty - 1;
	}
}

void	take_food(t_env *e, int type)
{
	int		i;

	i = e->user->player.ia.view[0][_food];
	add_todo(e, send_watch_sight, NULL);
	while (i != 0)
	{
		add_todo(e, send_take_item, type_to_str(type));
		i--;
	}
}

int			find_item(t_env *e, int type)
{
	int			nb;

//	printf("in find item \n");
	if (is_in_sight(e, type))
	{
		go_to(e);
		if (type == _food)
			take_food(e, type);
		else
			add_todo(e, send_take_item, type_to_str(type));
	}
	else
	{
//		printf("not_found \n");
		nb = rand_int(1, 4);
		if (nb <= 2)
			add_todo(e, send_move_forward, NULL);
		else if (nb == 3)
			add_todo(e, send_turn_right, NULL);
		else if (nb == 4)
			add_todo(e, send_turn_left, NULL);
	}
//	printf("out find item \n");
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
