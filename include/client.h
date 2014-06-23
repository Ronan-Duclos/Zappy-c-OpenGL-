/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/30 15:30:37 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/23 18:42:14 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <netdb.h>
# include <dirent.h>
# include <fcntl.h>
# include <common.h>
# include "libft.h"

# define OPT		"nph"

# define FD_SRV			1
# define FD_CLT			2
# define FD_FREE		0
# define MAX_CHANS		100
# define BUF_SIZE		4096

enum	e_travel
{
	_avance, _droite, _gauche
};

enum				e_ia
{
	_ia_food, _ia_evolve, _ia_max
};

typedef struct		s_opt
{
	int				port;
	char			*name;
	char			*host;
	int				x;
	int				y;
}					t_opt;

typedef int			(*t_fct_opt)(char **, t_opt *);

typedef struct		s_ia
{
	t_inv			inv;
	int				lvl;
	int				c_nbr;
	int				lvlup;
	int				x;
	int				y;
	t_inv			*view;
	int				*trvl;
	int				expulsed;
}					t_ia;

typedef struct		s_player
{
	char			*team;
	t_ia			ia;
	t_actions		acts[10];
	int				cur_aread;
	int				cur_awrite;
}					t_player;

typedef struct		s_user
{
	int				sock;
	int				ig;
	t_player		player;
	t_buf			buf_read;
	t_buf			buf_write;
	char			buf_read_tmp[BC_SIZE + 1];
	char			buf_write_tmp[BC_SIZE + 1];
}					t_user;

typedef struct		s_env
{
	t_opt			me;
	t_user			*user;
	char			**av;
	int				r;
	fd_set			fd_read;
	fd_set			fd_write;
}					t_env;

/*
**	c_opt.c
*/
int					get_clt_opt(t_opt *opt, int argc, char **argv);
/*
**	c_client.c
*/
int					create_clt(char *addr, int port);
void				check_fd(t_env *e);
void				do_select(t_env *e);
void				run_clt(t_env *e);
/*
**	c_tools1.c
*/
int						my_exit(int sig, char *line);
int						my_error(char c);
void					rcv_keyboard(t_env *e);
void					send_serveur(t_env *e);
void					rcv_serveur(t_env *e);

/*
**	Lexing functions
*/
int						get_inventaire(int *inv, char *str);
int						get_vision(t_inv **vis, int lvl, char *str);
/*
**	c_init.c
*/
void				init_clt(t_env *e);
/*
**	Fonctions des commandes
*/
void				drop_item(t_env *e);
void				take_item(t_env *e);
void				incantation(t_env *e);
int					death_clt(t_env *e);
/*
**	Fonctions "send" des commandes
*/
void				send_broadcast(t_env *e, char *msg);
void				send_connect_nbr(t_env *e);
void				send_drop_item(t_env *e, char *item);
void				send_expulse(t_env *e);
void				send_fork(t_env *e);
void				send_incantation(t_env *e);
void				send_inventaire(t_env *e);
void				send_move_forward(t_env *e);
void				send_take_item(t_env *e, char *item);
void				send_turn_left(t_env *e);
void				send_turn_right(t_env *e);
void				send_watch_sight(t_env *e);

/*
**	Fonctions "answer" des commandes
*/
void				receive_ok_only(t_env *e);
/*
**	IA
*/
void			my_ia(t_env *e);

#endif
