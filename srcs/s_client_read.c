/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_client_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 20:06:47 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/08 23:34:57 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "serveur.h"
#include "libft.h"

int		accept_gamer(t_env *e, int cs)
{
	char		*tmp;
	int			i;

	i = -1;
	e->users[cs]->ig = 1;
	e->users[cs]->player.team = ft_strdup(e->users[cs]->buf_read_tmp);
	e->users[cs]->player.cur_acts = 0;
	while (++i < 10)
		e->users[cs]->player.acts[i].time = 0;
	tmp = ft_itoa(cs);
	tmp_to_bc(&e->users[cs]->buf_write, tmp, 1);
	free(tmp);
	tmp = ft_itoa(e->opt.x);
	tmp_to_bc(&e->users[cs]->buf_write, tmp, 0);
	free(tmp);
	char_to_bc(&e->users[cs]->buf_write, ' ');
	tmp = ft_itoa(e->opt.y);
	tmp_to_bc(&e->users[cs]->buf_write, tmp, 1);
	free(tmp);
	send_inv(e, cs);
	return (1);
}

void	check_team(t_env *e, int cs)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (e->opt.name[i] != NULL)
	{
		if (ft_strcmp(e->users[cs]->buf_read_tmp, e->opt.name[i]) == 0)
			j = accept_gamer(e, cs);
		i++;
	}
	if (j == 0)
	{
		tmp_to_bc(&e->users[cs]->buf_write, "Wrong team name.", 1);
		close(cs);
		destroy_clt(e, cs);
	}
}

void	make_cmd(t_env *e, int cs)
{
	char	*tmp;

	tmp = ft_strchr(e->users[cs]->buf_read_tmp, '\n');
	tmp[0] = '\0';
	if (e->users[cs]->ig != 1)
		check_team(e, cs);
	/*else*/
}

void	client_read(t_env *e, int cs)
{
	int		r;

	r = recv(cs, e->users[cs]->buf_read_tmp, BC_SIZE, 0);
	if (r <= 0)
	{
		close(cs);
		destroy_clt(e, cs);
	}
	else
	{
		e->users[cs]->buf_read_tmp[r] = '\0';
		tmp_to_bc(&e->users[cs]->buf_read, e->users[cs]->buf_read_tmp, 0);
		if (verify_bsn(&e->users[cs]->buf_read) == 1)
		{
			bc_to_tmp(&e->users[cs]->buf_read, e->users[cs]->buf_read_tmp);
			printf("Receive : %s", e->users[cs]->buf_read_tmp);
			make_cmd(e, cs);
			e->users[cs]->buf_read_tmp[0] = '\0';
		}
	}
}
