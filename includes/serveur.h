/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/30 13:27:51 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/12 15:11:53 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <unistd.h>
# include <netdb.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <time.h>
# include <sys/select.h>
# include <common.h>
# include <conf.h>

# define					OPT			"pxynct"

# define FD_SRV				1
# define FD_CLT				2
# define FD_GFX				3
# define FD_FREE			0

typedef t_inv**		t_map;

typedef struct		s_opt
{
	int				port;
	int				x;
	int				y;
	char			**name;
	int				client;
	int				time;
}					t_opt;

typedef struct		s_user
{
	int				type;
	t_buf			buf_read;
	t_buf			buf_write;
	int				ig;
	t_player		player;
	void			(*fct_read)();
	void			(*fct_write)();
	char			buf_read_tmp[BC_SIZE + 1];
	char			buf_write_tmp[BC_SIZE + 1];
}					t_user;

typedef struct		s_srv
{
	int				max_fd;
	int				nb_p;
	int				max;
	int				r;
	fd_set			fd_read;
	fd_set			fd_write;
}					t_srv;

typedef struct		s_env
{
	t_opt			opt;
	t_map			map;
	t_srv			srv;
	t_user			**users;
}					t_env;

typedef int			(*t_fct_opt)(char **, t_opt *);

int					get_serv_opt(t_opt *opt, int argc, char **argv);

t_map				generate_map(t_env *env, int x, int y);

/*
**	s_client_read.c
*/
void				client_read(t_env *e, int cs);
/*
**	s_client_write.c
*/
void				client_write(t_env *e, int cs);
/*
**	s_deal_fd.c
*/
void				create_clt(t_env *e, int s);
void				destroy_clt(t_env *e, int sock);
void				init_fd(t_env *e);
void				check_fd(t_env *e);
/*
**	s_init.c
*/
int					init_sock(int port, t_env *e);
void				init_inv(t_user *user);
void				init_pos(t_user *user, int width, int height);
void				init_users(t_env *e);
void				init_serv(t_env *e);
/*
**	s_serveur.c
*/
void				run_serv(t_env *e);
int					main(int ac, char **av);
/*
**	s_inv.c
*/
void				send_inv(t_env *e, int id);

#endif
