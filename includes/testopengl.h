/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testopengl.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 17:09:45 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/07 17:52:37 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTOPENGL_H
# define TESTOPENGL_H

# include <GLUT/glut.h>

# define FLAG_LEFT		0x01
# define FLAG_DOWN		0x02
# define FLAG_RIGHT		0x04
# define FLAG_UP		0x08
# define FLAG_X			0x10
# define FLAG_Y			0x20
# define FLAG_Z			0x40
# define FLAG_W			0x80

# define CASE_MAX_ITEMS	256

# define SCR_WID		640
# define SCR_HGH		480

# define SQUARE(v)		(v * v)
# define MAG(va)		(sqrt(SQUARE(va[0]) + SQUARE(va[1]) + SQUARE(va[2])))

enum			e_colors
{
	_red,
	_white,
	_blue,
	_green,
	_yellow,
	_pink,
	_cyan
};

typedef struct	s_square
{
	char		tile;
	char		grid[256];
}				t_square;

typedef struct	s_env
{
	int			mapw;
	int			maph;
	t_square	*sq;
	GLuint		maptex;
	GLuint		egg[16];
	int			keys;
	GLfloat		camtrans[3];
	GLuint		lists;
	GLuint		vbo_vrtx;
	GLuint		vbo_nrms;
	GLuint		vbo_indx;
	GLuint		colors[7];
	GLdouble	winx;
	GLdouble	winy;
	GLdouble	realpos00[3];
	GLdouble	realpos0y[3];
	GLdouble	realposxy[3];
}				t_env;

t_env				*g_env;
static GLfloat		g_x = -0.5;
static GLfloat		g_y = -10.1;
static GLfloat		g_z = -30.0;

void			*load_file(char *filename);

#endif
