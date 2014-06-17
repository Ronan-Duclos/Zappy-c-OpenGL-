/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_expulse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/16 21:22:16 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/16 23:22:56 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <serveur.h>
#include <common.h>

void	expulse_north(t_env *e, t_user *expulsed)
{
	int		cs;
	int		direc;

	cs = expulsed->sock;
	direc = 5;
	remove_user_on_map(e, cs);
	if (expulsed->player.y == 0)
		expulsed->player.y = e->opt.y - 1;
	else
		expulsed->player.y--;
	put_user_on_map(e, cs);
	tmp_to_bc(&e->users[cs]->buf_write, "deplacement ", 0);
	if (expulsed->player.direc == NORTH)
		direc = 0;
	else if (expulsed->player.direc == WEST)
		direc = 1;
	else if (expulsed->player.direc == SOUTH)
		direc = 2;
	else if (expulsed->player.direc == EAST)
		direc = 3;
	char_to_bc(&e->users[cs]->buf_write, '0' + direc);
	tmp_to_bc(&e->users[cs]->buf_write, "\0", 1);
}

void	expulse_south(t_env *e, t_user *expulsed)
{
	int		cs;
	int		direc;

	cs = expulsed->sock;
	direc = 5;
	remove_user_on_map(e, cs);
	expulsed->player.y = (expulsed->player.y + 1) % e->opt.y;
	put_user_on_map(e, cs);
	tmp_to_bc(&e->users[cs]->buf_write, "deplacement ", 0);
	if (expulsed->player.direc == NORTH)
		direc = 0;
	else if (expulsed->player.direc == WEST)
		direc = 1;
	else if (expulsed->player.direc == SOUTH)
		direc = 2;
	else if (expulsed->player.direc == EAST)
		direc = 3;
	char_to_bc(&e->users[cs]->buf_write, '0' + direc);
	tmp_to_bc(&e->users[cs]->buf_write, "\0", 1);
}

void	expulse_west(t_env *e, t_user *expulsed)
{
	int		cs;
	int		direc;

	cs = expulsed->sock;
	direc = 5;
	remove_user_on_map(e, cs);
	if (expulsed->player.x == 0)
		expulsed->player.x = e->opt.x - 1;
	else
		expulsed->player.x--;
	put_user_on_map(e, cs);
	tmp_to_bc(&e->users[cs]->buf_write, "deplacement ", 0);
	if (expulsed->player.direc == NORTH)
		direc = 0;
	else if (expulsed->player.direc == WEST)
		direc = 1;
	else if (expulsed->player.direc == SOUTH)
		direc = 2;
	else if (expulsed->player.direc == EAST)
		direc = 3;
	char_to_bc(&e->users[cs]->buf_write, '0' + direc);
	tmp_to_bc(&e->users[cs]->buf_write, "\0", 1);
}

void	expulse_east(t_env *e, t_user *expulsed)
{
	int		cs;
	int		direc;
	
	cs = expulsed->sock;
	direc = 5;
	remove_user_on_map(e, cs);
	expulsed->player.x = (expulsed->player.x + 1) % e->opt.x;
	put_user_on_map(e, cs);
	tmp_to_bc(&e->users[cs]->buf_write, "deplacement ", 0);
	if (expulsed->player.direc == NORTH)
		direc = 0;
	else if (expulsed->player.direc == WEST)
		direc = 1;
	else if (expulsed->player.direc == SOUTH)
		direc = 2;
	else if (expulsed->player.direc == EAST)
		direc = 3;
	char_to_bc(&e->users[cs]->buf_write, '0' + direc);
	tmp_to_bc(&e->users[cs]->buf_write, "\0", 1);
}

void		expulse(t_env *e, int cs)
{
	t_player	*me;
	t_user		*expulsed;
	void		(*fct_direc[4])() = {

	expulse_north,
	expulse_east,
	expulse_south,
	expulse_west};
	me = &e->users[cs]->player;
	expulsed = e->map[me->x][me->y].player;
	while (expulsed != NULL)
	{
		if (expulsed->sock != cs)
			fct_direc[expulsed->player.direc](e, expulsed);
		expulsed = expulsed->next;
	}
}
