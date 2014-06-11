/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 18:52:47 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/11 11:57:40 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_H
# define GFX_H

#include "common.h"

# define XV(err,res,str)		(x_void(err,res,str,__FILE__))
# define X(err,res,str)			(x_int(err,res,str,__FILE__))

typedef struct		s_fd
{	t_buf			buf_read;
	t_buf			buf_write;
	void			(*fct_read)();
	void			(*fct_write)();
	char			buf_read_tmp[BC_SIZE + 1];
	char			buf_write_tmp[BC_SIZE + 1];
}					t_fd;

typedef struct		s_ipv
{
	int				port;
	int				sock;
	t_fd			fd;
}					t_ipv;

#endif
