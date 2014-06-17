/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 18:52:47 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/16 19:28:09 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_H
# define GFX_H

# include "gfx_gl.h"
# include "common.h"
# include <sys/select.h>

# define	BUF_SIZE	4096

enum				e_states
{
	_connect, _draw
};

typedef struct		s_fd
{
	t_buf	buf_read;
	t_buf	buf_write;
	char	buf_read_tmp[BC_SIZE + 1];
	char	buf_write_tmp[BC_SIZE + 1];
}					t_fd;

typedef struct		s_ipv
{
	int		port;
	int		sock;
	int		r;
	int		state;
	t_fd	fd;
	fd_set	fd_read;
	fd_set	fd_write;
	t_env	env;
}					t_ipv;

/*
**	g_ipv.c
*/
void		get_opt(t_ipv *ipv, int ac, char **av);
void		ipv_init(t_ipv *ipv, int ac, char **av);
void		ipv_loop(t_ipv *i);

/*
**	g_serv.c
*/
void		dtab_del(char **tab);
void		dtab_put(char **tab);
void		srv_read(t_ipv *ipv);
void		srv_write(t_ipv *ipv);
void		srv_connect(t_ipv *ipv, char **av);

/*
**	g_fds.c
*/
void		fds_init(t_ipv *ipv);
void		fds_check(t_ipv *ipv);

/*
**	g_cmd.c
*/
int			get_next_int(int *nb, char *s);
void		cmd_msz(char *cmd);
void		cmd_sgt(char *cmd);
void		cmd_bct(char *cmd);
void		cmd_check(t_ipv *ipv, char *buf);

/*
**	g_connect.c (3 statics)
*/
void		cmd_connect(t_ipv *ipv, char **tab);

/*
**	g_map.c (1 static)
*/
void		map_init(void);

#endif
