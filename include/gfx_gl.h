/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_gl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 18:07:00 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/20 22:27:39 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_GL_H
# define GFX_GL_H

# include <GLUT/glut.h>
# include "mdx.h"
# include "common.h"
# include "libft.h"

# define FLAG_LEFT		0x01
# define FLAG_DOWN		0x02
# define FLAG_RIGHT		0x04
# define FLAG_UP		0x08
# define FLAG_X			0x10
# define FLAG_Y			0x20
# define FLAG_Z			0x40
# define FLAG_W			0x80

# define CASE_MAX_ITEMS	256
# define NPCS_MAX		255

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

# define FOOD_OFFSET			0
# define LINEMATE_OFFSET		(FOOD_OFFSET + FOOD_PER_SQUARE)
# define DERAUMERE_OFFSET		(LINEMATE_OFFSET + LINEMATE_PER_SQUARE)
# define SIBUR_OFFSET			(DERAUMERE_OFFSET + DERAUMERE_PER_SQUARE)
# define MENDIANE_OFFSET		(SIBUR_OFFSET + SIBUR_PER_SQUARE)
# define PHIRAS_OFFSET			(MENDIANE_OFFSET + MENDIANE_PER_SQUARE)
# define THYSTAME_OFFSET		(PHIRAS_OFFSET + PHIRAS_PER_SQUARE)

# define SQUARE(v)		(v * v)
# define MAG(va)		(sqrt(SQUARE(va[0]) + SQUARE(va[1]) + SQUARE(va[2])))

enum			e_colors
{
	_white,
	_red,
	_blue,
	_green,
	_yellow,
	_pink,
	_cyan,
	_highlight,
	_init_item_pos,
	_init_plant_pos,
	_init_owl_pos,
	_lists_nb
};

enum			e_textures
{
	_grass,
	_plant
};

enum			e_models
{
	_mod_stone,
	_mod_plant,
	_mod_owl,
	_mod_nb
};

enum			e_vbos
{
	_vbo_vrtx,
	_vbo_nrms,
	_vbo_texp,
	_vbo_indx,
	_vbo_nb
};

enum			e_coord
{
	_x,
	_y,
	_z
};

typedef struct	s_square
{
	char			tile;
	unsigned char	grid[256];
	int				itms[_itm_nb];
	t_list			*anims;
	t_list			*mobs;
}					t_square;

typedef struct	s_anim	t_anim;

typedef struct	s_move
{
	int			frames;
	GLfloat		pos[3];
	GLfloat		dir[3];
}				t_move;

typedef struct	s_item
{
	GLuint		list;
	GLuint		id_nb;
	GLuint		vbo;
	t_anim		*anim;
}				t_item;

typedef struct	s_mob
{
	int			id;
	t_move		*move;
	t_anim		*anim;
}				t_mob;

typedef struct	s_npc
{
	int			x;
	int			y;
	t_inv		inv;
	int			dir;
	int			id;
	int			lvl;
	t_square	*sq;
	char		*team;
}				t_npc;

struct			s_anim
{
	int			frame;
	int			maxframe;
	void		(*fct)(t_anim *);
	char		dead;
};

typedef struct	s_env
{
	int			mapw;
	int			maph;
	int			time;
	char		**tnames;
	int			max_teams;
	t_square	*sq;
	int			keys;
	GLfloat		camtrans[3];
	GLuint		lists[_lists_nb];
	GLuint		vbos[_mod_nb][_vbo_nb];
	int			vbosizes[_mod_nb][_vbo_nb];
	GLdouble	winx;
	GLdouble	winy;
	GLdouble	realpos00[3];
	GLdouble	realpos0y[3];
	GLdouble	realposxy[3];
	int			selectcase;
	GLuint		testex;
	GLuint		maptex;
	t_npc		*npc;
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
void			getdir(const GLdouble o[3], GLdouble dir[3]);
void			getdirf(const GLfloat o[3], GLfloat dir[3]);
void			map_intersection(GLdouble *inter, const GLdouble *a, GLdouble *b);
void			set_vecf(GLfloat vec[3], GLfloat x, GLfloat y, GLfloat z);

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
void			display_any(t_item *item);
/*
**	g_anim.c
*/
void			anim_rock(t_anim *a);
t_anim			*new_anim(int frame, int time, void (*fct)(t_anim *));

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
void			ft_vbo_from_mdx(t_mdx *mdx, GLuint *vbo, int *size);

/*
**	g_lists.c
*/
void			del_link(t_list **link, void (*ft)(void *));
t_list			*new_link(t_list *next, void *content);
void			switch_link(t_list **src, t_list **dst);

/*
**	g_item_actions.c
*/
t_item			*new_item(GLuint list, GLuint id_nb, GLuint vbo, t_anim *anim);
void			take_stone(int square, int stone);

/*
**	g_move.c
*/
t_move			*new_move(int frames, GLfloat pos[3], GLfloat dir[3]);
void			anim_move(t_move *m);
void			move_init(t_move *move, int x, int y);

/*
**	g_npc_action.c
*/
t_mob			*new_mob(t_anim *anim, t_move *move, int id);
void			add_mob(int npc, int x, int y);
void			move_mob(int npc, int x, int y);

/*
**	g_npc.c
*/
t_list			**find_mob(int npc);

/*
**	g_display_players.c
*/
void			display_all_mobs(void);

#endif
