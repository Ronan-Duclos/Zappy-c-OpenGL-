/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_gl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 22:15:42 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/25 18:39:42 by tmielcza         ###   ########.fr       */
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
# define TEAM_COLORS	125

# define SCR_WID		640
# define SCR_HGH		480
# define FPS			60

# define FOOD_PER_SQUARE		45
# define LINEMATE_PER_SQUARE	45
# define DERAUMERE_PER_SQUARE	40
# define SIBUR_PER_SQUARE		35
# define MENDIANE_PER_SQUARE	30
# define PHIRAS_PER_SQUARE		25
# define THYSTAME_PER_SQUARE	20
# define EGG_PER_SQUARE			15

# define FOOD_OFFSET			0
# define LINEMATE_OFFSET		(FOOD_OFFSET + FOOD_PER_SQUARE)
# define DERAUMERE_OFFSET		(LINEMATE_OFFSET + LINEMATE_PER_SQUARE)
# define SIBUR_OFFSET			(DERAUMERE_OFFSET + DERAUMERE_PER_SQUARE)
# define MENDIANE_OFFSET		(SIBUR_OFFSET + SIBUR_PER_SQUARE)
# define PHIRAS_OFFSET			(MENDIANE_OFFSET + MENDIANE_PER_SQUARE)
# define THYSTAME_OFFSET		(PHIRAS_OFFSET + PHIRAS_PER_SQUARE)
# define EGG_OFFSET				(THYSTAME_OFFSET + THYSTAME_PER_SQUARE)

# define COLF(x)				(x / 255.0)
# define RGBF(r,g,b)			COLF(r), COLF(g), COLF(b)

# define TURQUOISE_SPEC			{RGBF(40.0, 200.0, 200.0), 1.0}
# define TURQUOISE_DIFF			{RGBF(48.0, 213.0, 200.0), 1.0}
# define TURQUOISE_AMBI			{RGBF(20.0, 100.0, 100.0), 1.0}

# define LAPIS_SPEC				{RGBF(80.0, 80.0, 100.0), 1.0}
# define LAPIS_DIFF				{RGBF(38.0, 97.0, 156.0), 1.0}
# define LAPIS_AMBI				{RGBF(30.0, 30.0, 50.0), 1.0}

# define AMETHIST_SPEC			{RGBF(90.0, 50.0, 100.0), 1.0}
# define AMETHIST_DIFF			{RGBF(153.0, 102.0, 204.0), 1.0}
# define AMETHIST_AMBI			{RGBF(100.0, 70.0, 130.0), 1.0}

# define JASPER_SPEC			{RGBF(150.0, 100.0, 100.0), 1.0}
# define JASPER_DIFF			{RGBF(215.0, 59.0, 62.0), 1.0}
# define JASPER_AMBI			{RGBF(150.0, 30.0, 30.0), 1.0}

# define JADE_SPEC				{RGBF(100.0, 100.0, 100.0), 1.0}
# define JADE_DIFF				{RGBF(0.0, 168.0, 107.0), 1.0}
# define JADE_AMBI				{RGBF(30.0, 80.0, 80.0), 1.0}

# define PINK_SPEC				{RGBF(220.0, 90.0, 200.0), 1.0}
# define PINK_DIFF				{RGBF(255.0, 100.0, 234.0), 1.0}
# define PINK_AMBI				{RGBF(100.0, 50.0, 60.0), 1.0}

# define PERIDOT_SPEC			{RGBF(160.0, 130.0, 0.0), 1.0}
# define PERIDOT_DIFF			{RGBF(230.0, 205.0, 0.0), 1.0}
# define PERIDOT_AMBI			{RGBF(100.0, 100.0, 50.0), 1.0}

# define BLACK_SPEC				{RGBF(200.0, 200.0, 255.0), 0.9}
# define BLACK_DIFF				{RGBF(20.0, 30.0, 70.0), 0.8}
# define BLACK_AMBI				{RGBF(10.0, 10.0, 10.0), 1.0}

# define PI				3.14159265359
# define SQUARE(v)		(v * v)
# define MAG(va)		(sqrt(SQUARE(va[0]) + SQUARE(va[1]) + SQUARE(va[2])))
# define TORAD(a)		((float)a / 180 * PI)

enum			e_lists
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
	_init_egg_pos,
	_lists_nb
};

enum			e_textures
{
	_text_lower,
	_text_upper,
	_text_symbols,
	_tex_grass,
	_tex_plant,
	_tex_zepp,
	_tex_egg,
	_tex_totem,
	_tex_nb
};

enum			e_models
{
	_mod_stone,
	_mod_plant,
	_mod_owl1,
	_mod_owl2,
	_mod_owl3,
	_mod_egg,
	_mod_totem,
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

enum			e_colors
{
	_r,
	_g,
	_b
};

typedef struct	s_square
{
	char			tile;
	unsigned char	grid[CASE_MAX_ITEMS];
	int				itms[_itm_nb];
	t_list			*anims;
	t_list			*mobs;
	t_list			*egg;
}					t_square;

typedef struct	s_anim	t_anim;
typedef struct	s_move	t_move;

struct	s_move
{
	int			frame;
	int			maxframe;
	GLfloat		pos[3];
	GLfloat		dir[3];
	void		(*fct)(t_move *);
};

typedef struct	s_rot
{
	int			frames;
	GLfloat		vec[3];
	GLfloat		angle;
	GLfloat		rot;
}				t_rot;

typedef struct	s_item
{
	GLuint		list;
	GLuint		vbo;
	t_anim		*anim;
	void		(*fct)(struct s_item *);
}				t_item;

typedef struct	s_mob
{
	int			id;
	t_move		*move;
	t_rot		*rot;
	t_anim		*anim;
}				t_mob;

typedef struct	s_egg
{
	int			id;
	int			x;
	int			y;
	char		*team;
}				t_egg;

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

//Liste chainee de teams
typedef struct	s_env
{
	int			mapw;
	int			maph;
	int			time;
	char		**tnames;
	int			max_teams;
	t_square	*sq;
	t_list		*egg;
	int			keys;
	GLfloat		camtrans[3];
	GLuint		lists[_lists_nb];
	GLuint		textures[_tex_nb];
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
	GLuint		zepptex;
	t_npc		*npc;
	GLfloat		teamcol[TEAM_COLORS][3];
}				t_env;

t_env			*g_env;

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
void			map_intersection(GLdouble *i, const GLdouble *a, GLdouble *b);
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
void			display_any(t_item *i);
void			display_totem(t_item *i);
void			display_items(int sq);
void			display_any(t_item *item);
/*
**	g_anim.c
*/
void			anim_rock(t_anim *a);
t_anim			*new_anim(int frame, int time, void (*fct)(t_anim *));
void			anim_mob(t_anim *a);
void			anim_incant(t_anim *a);

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
void			ft_vbo_from_mdx(t_geoset geos, GLuint *vbo, int *size);

/*
**	g_lists.c
*/
void			del_link(t_list **link, void (*ft)(void *));
t_list			*new_link(t_list *next, void *content);
void			switch_link(t_list **src, t_list **dst);
void			add_link_end(t_list **list, void *content);

/*
**	g_item_actions.c
*/
t_item			*new_item(GLuint l, GLuint vbo, t_anim *a, void (*f)(t_item *));
void			take_stone(int square, int stone);

/*
**	g_move.c
*/
t_move			*new_move(int frame, int max, GLfloat pos[3], GLfloat dir[3]);
void			anim_move(t_move *m);
void			anim_move2(t_move *m);
void			move_init(t_move *move, int x, int y, int z);

/*
**	g_npc_action.c
*/
void			add_mob(int npc, int x, int y, enum e_dir dir);
void			move_mob(int npc, int x, int y, enum e_dir dir);
void			kill_mob(int npc);
void			lower_mob(int npc);

/*
**	g_npc.c
*/
t_list			**find_mob(int npc);
t_mob			*new_mob(t_anim *anim, t_move *move, t_rot *rot, int id);
void			del_mob(void *ptr);
int				is_in_list(t_list *link, t_list *list);

/*
**	g_display_players.c
*/
void			display_all_mobs(void);

/*
**	g_rot.c
*/
t_rot			*new_rot(int frames, GLfloat vec[3], GLfloat a, GLfloat r);
void			anim_rot(t_rot *r);
void			rot_init(t_rot *rot, enum e_dir dir);

/*
**	g_incant_action.c
*/
void			cast_incant(int x, int y);
void			repel_incant(int x, int y);

#endif
