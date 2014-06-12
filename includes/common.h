/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/30 16:10:52 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/12 17:09:02 by dmansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "stdio.h"

# define NB_STONE	6
# define BC_SIZE	40960
# define BC_SIZE2	BC_SIZE - 1

# define XV(err,res,str)	(x_void(err,res,str,__FILE__))
# define X(err,res,str)		(x_int(err,res,str,__FILE__))

# define NORTH				0
# define EAST				1
# define SOUTH				2
# define WEST				3

enum				e_stone
{
	_food, _linemate, _deraumere, _sibur, _mendiane, _phiras, _thystame
};

typedef int			t_inv[NB_STONE + 1];

typedef struct		s_actions
{
	int				cs;
	double			time;
	void			(*fct_cmd)();
}					t_actions;

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

typedef struct		s_buf
{
	char			start[BC_SIZE];
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
/*
**	buf_circle.c
*/
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
