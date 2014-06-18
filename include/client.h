/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/30 15:30:37 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/18 19:51:50 by rbernand         ###   ########.fr       */
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

# define OPT				"nph"

# define FD_SRV				1
# define FD_CLT				2
# define FD_FREE			0
# define MAX_CHANS			100

typedef struct s_env	t_env;
typedef struct s_user	t_user;

typedef struct			s_opt
{
	int					port;
	char				*name;
	char				*host;
}						t_opt;

typedef int				(*t_fct_opt)(char **, t_opt *);

typedef struct		s_map
{
	t_inv			ground;
}					t_map;

typedef struct		s_player
{
	char			*team;
	t_inv			inv;
	int				lvl;
	t_map			**view;
	t_actions		acts[10];
	int				cur_aread;
	int				cur_awrite;
}					t_player;

struct					s_user
{
	int					sock;
	int					ig;
	t_player			player;
	t_buf				buf_read;
	t_buf				buf_write;
	char				buf_read_tmp[BC_SIZE + 1];
	char				buf_write_tmp[BC_SIZE + 1];
};

struct					s_env
{
	t_opt				me;
	t_user				*user;
	int					r;
	fd_set				fd_read;
	fd_set				fd_write;
};

/*
**	c_opt.c
*/
int						get_clt_opt(t_opt *opt, int argc, char **argv);
/*
**	c_client.c
*/
int						create_clt(char *addr, int port);
void					check_actions(t_env *e);
void					do_select(t_env *e);
void					run_clt(t_env *e);
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
int						get_inventaire(t_inv *inv, char *str);
int						get_vision(t_inv **inv, int lvl, char *str);
/*
**	c_init.c
*/
void					init_clt(t_env *e);

#endif