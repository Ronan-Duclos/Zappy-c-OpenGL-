/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/30 13:27:51 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/17 20:53:33 by rduclos          ###   ########.fr       */
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

# define OPT				"pxynct"

# define FD_SRV				1
# define FD_CLT				2
# define FD_GFX				3
# define FD_FREE			0

# define AVANCE				7

# define NBR_CMD			13
# define BUF_SIZE			4096

typedef struct		s_glst
{
	int				cs;
	struct s_glst	*next;
}					t_glst;

typedef struct		s_opt
{
	int				port;
	int				x;
	int				y;
	char			**name;
	int				client;
	int				time;
}					t_opt;

typedef struct		s_gfx
{
	int		i;
	int		j;
	int		x;
	int		state;
	int		gfx;
}					t_gfx;

typedef struct		s_player
{
	char			*team;
	t_inv			inv;
	t_actions		acts[10];
	int				cur_aread;
	int				cur_awrite;
	int				lvl;
	int				x;
	int				y;
	int				direc;
}					t_player;

typedef struct		s_user
{
	int				type;
	int				ig;
	t_gfx			gfx;
	t_buf			buf_read;
	t_buf			buf_write;
	int				sock;
	double			time; 
	t_player		player;
	void			(*fct_read)();
	void			(*fct_write)();
	char			buf_read_tmp[BC_SIZE + 1];
	char			buf_write_tmp[BC_SIZE + 1];
	struct s_user	*next;
}					t_user;

typedef struct		s_case
{
	t_inv			ground;
	t_user			*player;
}					t_case;

typedef struct		s_srv
{
	int				max_fd;
	int				nb_p;
	int				max;
	int				r;
	t_glst			*glst;
	fd_set			fd_read;
	fd_set			fd_write;
}					t_srv;

typedef struct		s_team
{
	char			*name;
	int				member;
}					t_team;

typedef struct		s_env
{
	t_opt			opt;
	t_case			**map;
	t_team			*team;
	t_srv			srv;
	t_user			**users;
}					t_env;

typedef struct		s_ponf_cmd
{
	char			*str;
	int				value;
	void			(*fct_cmd)();
}					t_ponf_cmd;

typedef int			(*t_fct_opt)(char **, t_opt *);

int					get_serv_opt(t_opt *opt, int argc, char **argv);

void				generate_map(t_env *env);

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
void				init_team(t_env *e);
int					init_sock(int port, t_env *e);
void				init_player(t_env *e, int cs);
void				init_users(t_env *e);
void				init_serv(t_env *e);

/*
**	serveur.c
*/
void				run_serv(t_env *e);
void				send_inv(t_env *e, int id);

/*
**	s_user_on_map.c
*/
void	put_user_on_map(t_env *e, int cs);
void	remove_user_on_map(t_env *e, int cs);

/*
**	s_gfx.c
*/
void				gfx_msz(t_env *e, int cs);
void				gfx_sgt(t_env *e, int cs);
void				gfx_bct(t_env *e, int cs, int x, int y);
void				gfx_mct(t_env *e, int cs);
void				gfx_tna(t_env *e, int cs);
void				gfx_pnw(t_env *e, int cs, int i);
void				gfx_enw(t_env *e, int cs);
void				gfx_ppo(t_env *e, int cs, int clt);

/*
**	s_gfx_init.c
*/
void				gfx_end_init(t_env *e);
void				gfx_init_send_tna(t_env *env, int cs);
void				gfx_init_send_pnw(t_env *env, int cs);
void				gfx_init(t_env *e, int cs);

/*
**	s_gfx_lst.c
*/
t_glst				*glst_new(int cs);
void				glst_add(t_glst **lst, t_glst *new);
void				glst_del_one(t_glst **lst, int cs);
void				glst_put(t_glst **lst);

/*
**	s_less_hp.c
*/
int					less_hp(t_env *e, int cs);

/*
**	Fonctions des différentes commandes client / server
*/
void				move_forward(t_env *e, int cs);
void				turn_right(t_env *e, int cs);
void				turn_left(t_env *e, int cs);
void				take_item(t_env *e, int cs);
void				drop_item(t_env *e, int cs);
void				watch_sight(t_env *e, int cs);
void				my_fork(t_env *e, int cs);
void				connect_nbr(t_env *e, int cs);
void				incantation(t_env *e, int cs);
void				expulse(t_env *e, int cs);
void				broadcast(t_env *e, int cs);

/*
**	s_watch_sight
*/
void	send_one_case(t_env *e, int cs, int x, int y);
void	watch_south(t_env *e, int cs);
void	watch_north(t_env *e, int cs);
void	watch_east(t_env *e, int cs);
void	watch_west(t_env *e, int cs);

#endif