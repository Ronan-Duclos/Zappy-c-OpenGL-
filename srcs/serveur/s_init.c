/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 19:08:44 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/27 11:08:53 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "common.h"
#include "libft.h"

void	init_team(t_env *e)
{
	char	**team;
	int		i;

	i = 0;
	team = e->opt.name;
	while (team[i] != NULL)
		i++;
	e->team = (t_team *)malloc(sizeof(t_team) * (i + 1));
	bzero(e->team, sizeof(t_team) * (i + 1));
	i = 0;
	while (team[i] != NULL)
	{
		e->team[i].eggs = NULL;
		e->team[i].name = team[i];
		e->team[i].member = e->opt.client;
		e->team[i].win = 0;
		i++;
	}
	e->nb_team = i;
}

int		init_sock(int port, t_env *e)
{
	int					sock;
	struct protoent		*prt;
	struct sockaddr_in	srv;

	srv.sin_family = AF_INET;
	srv.sin_port = htons(port);
	srv.sin_addr.s_addr = htonl(INADDR_ANY);
	prt = (struct protoent*)XV(NULL, getprotobyname("tcp"), "getprotobyname");
	sock = X(-1, socket(PF_INET, SOCK_STREAM, prt->p_proto), "socket");
	X(-1, bind(sock, (struct sockaddr*)&srv, sizeof(srv)), "bind");
	X(-1, listen(sock, 42), "listen");
	e->srv.max = sock;
	return (sock);
}

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

void	init_player(t_env *e, int cs, int team)
{
	double			time;
	t_egg			*egg;

	e->users[cs]->player.inc = 0;
	e->users[cs]->player.direc = rand() % 4;
	e->users[cs]->player.lvl = 1;
	time = ft_usec_time();
	if ((egg = e->team[team].eggs) == NULL)
	{
		e->users[cs]->player.x = rand() % e->opt.x;
		e->users[cs]->player.y = rand() % e->opt.y;
		e->users[cs]->player.inv[_food] = NB_START_FOOD;
		e->users[cs]->time = time;
	}
	else
	{
		e->users[cs]->player.x = egg->x;
		e->users[cs]->player.y = egg->y;
		e->users[cs]->player.inv[_food] = NB_START_FOOD;
		e->users[cs]->time = egg->t_eclos;
		gfx_send_egg(e, egg, gfx_ebo);
		del_egg(&e->team[team]);
	}
	put_user_on_map(e, cs);
	add_start_cal(e, cs, team);
}

void	init_users(t_env *e)
{
	int				i;
	int				j;
	struct rlimit	rlp;

	X(-1, getrlimit(RLIMIT_NOFILE, &rlp), "getrlimit");
	j = rlp.rlim_cur;
	e->srv.max_fd = j;
	e->users = (t_user **)XV(NULL, malloc(sizeof(t_user *) * j), "malloc");
	i = 0;
	e->srv.nb_p = 0;
	while (i < j)
	{
		e->users[i] = (t_user *)XV(NULL, malloc(sizeof(t_user)), "malloc");
		e->users[i]->type = FD_FREE;
		e->users[i]->player.team = NULL;
		e->users[i]->started = 0;
		init_bc(&e->users[i]->buf_read);
		init_bc(&e->users[i]->buf_write);
		e->users[i]->buf_read_tmp[0] = '\0';
		e->users[i]->buf_write_tmp[0] = '\0';
		e->users[i]->fct_read = client_read;
		e->users[i]->fct_write = client_write;
		i++;
	}
}
