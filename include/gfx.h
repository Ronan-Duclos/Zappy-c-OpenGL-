/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 18:52:47 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/23 15:03:22 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_H
# define GFX_H

# include "gfx_gl.h"
# include "common.h"
# include <sys/select.h>
# include <pthread.h>

# define	BUF_SIZE	4096
# define	CMDS_NB		12

enum				e_states
{
	_connect, _draw, _end
};

typedef struct		s_fd
{
	t_buf	buf_read;
	t_buf	buf_write;
	char	buf_read_tmp[BC_SIZE + 1];
	char	buf_write_tmp[BC_SIZE + 1];
}					t_fd;

typedef struct		s_cmd
{
	char	cmd[3];
	void	(*fu)();
}					t_cmd;

typedef struct		s_ipv
{
	int			port;
	int			sock;
	pthread_t	th;
	int			r;
	int			state;
	t_fd		fd;
	fd_set		fd_read;
	fd_set		fd_write;
	t_env		env;
}					t_ipv;

/*
**	g_ipv.c
*/
void		get_opt(t_ipv *ipv, int ac, char **av);
void		ipv_init(t_ipv *ipv, int ac, char **av);
void		*ipv_loop(void *args);

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
**	g_cmd_check.c
*/
int			get_next_int(int *nb, char *s);
void		cmd_check(t_ipv *ipv, char *buf);

/*
**	g_cmd.c
*/
void		cmd_msz(char *cmd);
void		cmd_sgt(char *cmd);
void		cmd_bct(char *cmd);
void		cmd_pnw(char *cmd);
void		cmd_ppo(char *cmd);
void		cmd_pin(char *cmd);
void		cmd_plv(char *cmd);
void		cmd_pgt(char *cmd);
void		cmd_pdr(char *cmd);
void		cmd_pdi(char *cmd);
void		cmd_pfk(char *cmd);
void		cmd_pic(char *cmd);
void		cmd_pie(char *cmd);

/*
**	g_cmd_send.c
*/
void		cmd_pin_send(t_ipv *ipv, int clt);
void		cmd_sgt_send(t_ipv *ipv);
void		cmd_plv_send(t_ipv *ipv, int clt);
void		cmd_smg_send(t_ipv *ipv, char *msg);

/*
**	g_connect.c (3 statics)
*/
void		cmd_connect(t_ipv *ipv, char **tab, int *i);

/*
**	g_map.c (1 static)
*/
void		map_init(void);

#endif
