/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_expulse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/16 21:22:16 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/26 23:52:08 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <serveur.h>
#include <common.h>

void			expulse_north(t_env *e, t_user *expulsed)
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
	tmp_to_bc(&expulsed->buf_write, "deplacement ", 0);
	if (expulsed->player.direc == NORTH)
		direc = 0;
	else if (expulsed->player.direc == WEST)
		direc = 1;
	else if (expulsed->player.direc == SOUTH)
		direc = 2;
	else if (expulsed->player.direc == EAST)
		direc = 3;
	char_to_bc(&expulsed->buf_write, '0' + direc);
	tmp_to_bc(&expulsed->buf_write, "\0", 1);
}

void			expulse_south(t_env *e, t_user *expulsed)
{
	int		cs;
	int		direc;

	cs = expulsed->sock;
	direc = 5;
	remove_user_on_map(e, cs);
	expulsed->player.y = (expulsed->player.y + 1) % e->opt.y;
	put_user_on_map(e, cs);
	tmp_to_bc(&expulsed->buf_write, "deplacement ", 0);
	if (expulsed->player.direc == NORTH)
		direc = 0;
	else if (expulsed->player.direc == WEST)
		direc = 1;
	else if (expulsed->player.direc == SOUTH)
		direc = 2;
	else if (expulsed->player.direc == EAST)
		direc = 3;
	char_to_bc(&expulsed->buf_write, '0' + direc);
	tmp_to_bc(&expulsed->buf_write, "\0", 1);
}

void			expulse_west(t_env *e, t_user *expulsed)
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
	tmp_to_bc(&expulsed->buf_write, "deplacement ", 0);
	if (expulsed->player.direc == NORTH)
		direc = 0;
	else if (expulsed->player.direc == WEST)
		direc = 1;
	else if (expulsed->player.direc == SOUTH)
		direc = 2;
	else if (expulsed->player.direc == EAST)
		direc = 3;
	char_to_bc(&expulsed->buf_write, '0' + direc);
	tmp_to_bc(&expulsed->buf_write, "\0", 1);
}

void			expulse_east(t_env *e, t_user *expulsed)
{
	int		cs;
	int		direc;

	cs = expulsed->sock;
	direc = 5;
	remove_user_on_map(e, cs);
	expulsed->player.x = (expulsed->player.x + 1) % e->opt.x;
	put_user_on_map(e, cs);
	tmp_to_bc(&expulsed->buf_write, "deplacement ", 0);
	if (expulsed->player.direc == NORTH)
		direc = 0;
	else if (expulsed->player.direc == WEST)
		direc = 1;
	else if (expulsed->player.direc == SOUTH)
		direc = 2;
	else if (expulsed->player.direc == EAST)
		direc = 3;
	char_to_bc(&expulsed->buf_write, '0' + direc);
	tmp_to_bc(&expulsed->buf_write, "\0", 1);
}

void			expulse(t_env *e, int cs)
{
	t_player			*me;
	t_user				*expulsed;
	int					i;
	static void			(*fct_direc[4])() = {

	expulse_north,
	expulse_east,
	expulse_south,
	expulse_west};
	i = 0;
	me = &e->users[cs]->player;
	expulsed = e->map[me->y][me->x].player;
	while (expulsed != NULL)
	{
		if (expulsed->sock != cs)
		{
			fct_direc[expulsed->player.direc](e, expulsed);
			i++;
		}
		expulsed = expulsed->next;
	}
	if (i == 0)
		tmp_to_bc(&e->users[cs]->buf_write, "ko", 1);
	else
		tmp_to_bc(&e->users[cs]->buf_write, "ok", 1);
}
