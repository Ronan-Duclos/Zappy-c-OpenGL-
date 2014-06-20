/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/30 16:10:52 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/20 23:11:33 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

#include <stdio.h>

# define XV(err,res,str)	(x_void(err,res,str,__FILE__))
# define X(err,res,str)		(x_int(err,res,str,__FILE__))
# define NB_STONE			6
# define BC_SIZE			10000
# define BC_SIZE2			BC_SIZE - 1
# define NORTH				0
# define EAST				1
# define SOUTH				2
# define WEST				3

enum				e_map
{
	_food, _linemate, _deraumere, _sibur, _mendiane, _phiras, _thystame, _player
};

enum				e_fuck_robin
{
	_itm_nb = 7
};

typedef int			t_inv[_itm_nb + 1];

typedef struct		s_actions
{
	char			*cmd;
	char			*answer;
	double			time;
	double			start;
	void			(*fct_cmd)();
	void			(*fct_gfx)();
}					t_actions;

typedef struct		s_buf
{
	char			start[BC_SIZE + 1];
	char			*end;
	char			*head;
	char			*head2;
	char			*tail;
	int				nb_cmd;
}					t_buf;

/*
**	functions.c
*/
int		rand_int(int min, int max);
int		get_vision_nb_cell(int level);
char	*type_to_str(int id);
int			str_to_type(char *str);
/*
**	buf_circle.c
*/
void	display_bc(t_buf *bc);
void	init_bc(t_buf *buf);
int		verify_bsn(t_buf *buf);
void	tmp_to_bc(t_buf *buf, char *str, int type);
void	char_to_bc(t_buf *buf, char c);
void	bc_to_tmp(t_buf *buf, char *tmp);
/*
**error.c
*/
int					x_int(int err, int res, char *str, char *file);
void				*x_void(void *err, void *res, char *str, char *file);
/*
**  my_time.h
*/
double      ft_usec_time(void);

#endif
