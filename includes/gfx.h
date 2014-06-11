/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 18:52:47 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/11 18:49:49 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_H
# define GFX_H

# include "common.h"
# include <sys/select.h>

# define	BUF_SIZE	4096

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
	int		connected;
	t_fd	fd;
	fd_set	fd_read;
	fd_set	fd_write;
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
void		srv_read(t_ipv *ipv);
void		srv_write(t_ipv *ipv);
void		srv_connect(t_ipv *ipv, char **av);

/*
**	g_fds.c
*/
void		fds_init(t_ipv *ipv);
void		fds_check(t_ipv *ipv);

void		dtab_put(char **tab);
void		cmd_connect(t_ipv *ipv, char *buf);

#endif
