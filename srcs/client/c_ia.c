/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_ia.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/23 22:59:41 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/25 01:36:51 by rduclos          ###   ########.fr       */
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
	if (e->user->ig == 1 && e->user->player.acts[aw].time == 0 &&
		e->user->player.acts[ar].wait != 1)
	{
		if (e->user->player.ia.todo == NULL)
			my_ia(e);
		else
			todo_to_cal(e);
	}
}

void	my_ia(t_env *e)
{
	static int		i = 1;

	if (i == 0)
	{
		add_todo(e, send_inventaire, NULL);
		add_todo(e, send_watch_sight, NULL);
		i = 1;
	}
	else
	{
		what_i_do(e);
		i = 0;
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

int			what_i_do(t_env *e)
{

	find_item(e, _food);
/*
	need = what_i_need(e, &e->user->player.ia);
	if (need == _food)
	{
		printf("in what i do\n");
		i_need_to_eat(e);
	}
	*/
	return (0);
}


void		i_have_stone()
{
	
}

int			what_i_need(t_env *e, t_ia *ia)
{
	if (ia->inv[_food] < MIN_FOOD)
		return (_ia_food);
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
//	printf("vision in sight %d\n", e->user->nb_cmd);
/*	int a;
	a = 0;
	t_inv *b;
	while (a < get_vision_nb_cell(e->user->player.ia.lvl))
	{
		b = &e->user->player.ia.view[a];
		printf("%d %d %d %d %d %d %d %d \n", *b[0], *b[1], *b[2], *b[3], *b[4], *b[5], *b[6], *b[7]);
		a++;
	}*/
	while (++i < max)
	{
//		printf("in is in sight | %d items in %d\n", e->user->player.ia.view[i][type], i);
		if (e->user->player.ia.view[i][type] > 0)
		{
			j = 0;
			while (i > (get_vision_nb_cell(j) - 1))
			{
//				printf("i : %d // j : %d\n", i, get_vision_nb_cell(j));
				j++;
			}
			e->user->player.ia.destx = j;
			e->user->player.ia.desty = i - get_middle(e->user->player.ia.lvl);
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

int			find_item(t_env *e, int type)
{
	int			nb;

//	printf("in find item \n");
	if (is_in_sight(e, type))
	{
		go_to(e);
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
