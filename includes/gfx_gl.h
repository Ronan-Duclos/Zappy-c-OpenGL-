/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_gl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 18:07:00 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/14 15:23:52 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_GL_H
# define GFX_GL_H

# include <GLUT/glut.h>
# include "mdx.h"
# include "common.h"

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
# define FPS			60

# define FOOD_PER_SQUARE		66
# define LINEMATE_PER_SQUARE	60
# define DERAUMERE_PER_SQUARE	50
# define SIBUR_PER_SQUARE		35
# define MENDIANE_PER_SQUARE	20
# define PHIRAS_PER_SQUARE		15
# define THYSTAME_PER_SQUARE	10

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
	_cyan,
	_highlight,
	_init_item_pos,
	_lists_nb
};

typedef struct	s_anim	t_anim;

typedef struct	s_moving
{
	GLfloat		pos[3];
	GLfloat		dir[3];
}				t_moving;

struct			s_anim
{
	int			frame;
	int			maxframe;
	void		(*ft)(t_anim *);
	char		dead;
};

typedef struct	s_square
{
	char			tile;
	unsigned char	grid[256];
	int				itms[_itm_nb];
}					t_square;

typedef struct	s_env
{
	int			mapw;
	int			maph;
	int			time;
	t_square	*sq;
	GLuint		maptex;
	GLuint		egg[16];
	int			keys;
	GLfloat		camtrans[3];
	GLuint		lists[_lists_nb];
	GLuint		vbo_vrtx;
	GLuint		vbo_nrms;
	GLuint		vbo_indx;
	GLdouble	winx;
	GLdouble	winy;
	GLdouble	realpos00[3];
	GLdouble	realpos0y[3];
	GLdouble	realposxy[3];
	int			selectcase;
}				t_env;

t_env				*g_env;

void			*load_file(char *filename);

/*
**	g_colors1.c
*/
void			list_white_init(void);
void			list_red_init(void);
void			list_blue_init(void);
void			list_green_init(void);
void			list_yellow_init(void);

/*
**	g_colors2.c
*/
void			list_pink_init(void);
void			list_cyan_init(void);
void			list_highlight_init(void);

/*
**	g_env.c (1 static)
*/
void			env_init(t_env *env);

/*
**	g_item_list.c
*/
void			list_item_init(t_env *env);

/*
**	g_glut.c
*/
void			init_glut(int ac, char **av);

/*
**	g_gl.c
*/
void			gl_init(void);

/*
**	g_light.c
*/
void			light_init(void);

/*
**	g_display.c
*/
void			display(void);

/*
**	g_input.c
*/
void			speckeyup(int key, int xmouse, int ymouse);
void			speckey(int key, int xmouse, int ymouse);
void			motion(int x, int y);

/*
**	g_event.c
*/
void			idle(void);
void			reshape(int w, int h);

/*
**	g_transpose.c
*/
void			transpose(void);

/*
**	g_time.c
*/
int				time_frame(void);

/*
**	g_vec.c
*/
void			normalize(GLdouble vec[3]);
void			getdir(GLdouble o[3], GLdouble dir[3]);
void			map_intersection(GLdouble *inter, GLdouble *a, GLdouble *b);

/*
**	g_display_map.c
*/
void			display_map(void);

/*
**	g_display_squares.c (1 static)
*/
void			display_all_squares(void);

/*
**	g_display_grid.c (1 static)
*/
void			display_all_grid(void);

/*
**	g_display_items (1 static)
*/
void			display_items(int sq);

/*
**	g_anim.c
*/
void			anim_rock(t_anim *a);

/*
**	g_bmp.c (1 static)
*/
GLuint			load_bmp_tex(char *f);

/*
**	g_resources.c
*/
void			resources_load(t_env *e);

/*
**	g_vbo.c
*/
void			ft_vbo_from_mdx(t_mdx *mdx);

#endif
