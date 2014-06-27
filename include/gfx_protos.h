/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_protos.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 18:12:36 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/27 10:54:15 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_PROTOS_H
# define GFX_PROTOS_H

# include <GLUT/glut.h>
# include "mdx.h"
# include "common.h"
# include "libft.h"

# define FLAG_LEFT				0x01
# define FLAG_DOWN				0x02
# define FLAG_RIGHT				0x04
# define FLAG_UP				0x08
# define FLAG_X					0x10
# define FLAG_Y					0x20
# define FLAG_Z					0x40
# define FLAG_W					0x80

# define CASE_MAX_ITEMS			256
# define NPCS_MAX				255
# define TEAM_COLORS			125

# define SCR_WID				1280
# define SCR_HGH				960
# define FPS					60

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

# define COLF(x)		(x / 255.0)
# define RGBF(r,g,b)	COLF(r), COLF(g), COLF(b)

# define TURQUOISE_SPEC	{RGBF(40.0, 200.0, 200.0), 1.0}
# define TURQUOISE_DIFF	{RGBF(48.0, 213.0, 200.0), 1.0}
# define TURQUOISE_AMBI	{RGBF(20.0, 100.0, 100.0), 1.0}

# define LAPIS_SPEC		{RGBF(80.0, 80.0, 100.0), 1.0}
# define LAPIS_DIFF		{RGBF(38.0, 97.0, 156.0), 1.0}
# define LAPIS_AMBI		{RGBF(30.0, 30.0, 50.0), 1.0}

# define AMETHIST_SPEC	{RGBF(90.0, 50.0, 100.0), 1.0}
# define AMETHIST_DIFF	{RGBF(153.0, 102.0, 204.0), 1.0}
# define AMETHIST_AMBI	{RGBF(100.0, 70.0, 130.0), 1.0}

# define JASPER_SPEC	{RGBF(150.0, 100.0, 100.0), 1.0}
# define JASPER_DIFF	{RGBF(215.0, 59.0, 62.0), 1.0}
# define JASPER_AMBI	{RGBF(150.0, 30.0, 30.0), 1.0}

# define JADE_SPEC		{RGBF(100.0, 100.0, 100.0), 1.0}
# define JADE_DIFF		{RGBF(0.0, 168.0, 107.0), 1.0}
# define JADE_AMBI		{RGBF(30.0, 80.0, 80.0), 1.0}

# define PINK_SPEC		{RGBF(220.0, 90.0, 200.0), 1.0}
# define PINK_DIFF		{RGBF(255.0, 100.0, 234.0), 1.0}
# define PINK_AMBI		{RGBF(100.0, 50.0, 60.0), 1.0}

# define PERIDOT_SPEC	{RGBF(160.0, 130.0, 0.0), 1.0}
# define PERIDOT_DIFF	{RGBF(230.0, 205.0, 0.0), 1.0}
# define PERIDOT_AMBI	{RGBF(100.0, 100.0, 50.0), 1.0}

# define BLACK_SPEC		{RGBF(200.0, 200.0, 255.0), 0.9}
# define BLACK_DIFF		{RGBF(20.0, 30.0, 70.0), 0.8}
# define BLACK_AMBI		{RGBF(10.0, 10.0, 10.0), 1.0}

# define PI			3.14159265359
# define SQUARE(v)	(v * v)
# define MAG(va)	(sqrt(SQUARE(va[0]) + SQUARE(va[1]) + SQUARE(va[2])))
# define TORAD(a)	((float)a / 180 * PI)

# define ACC_ITM(x)	((t_item *)(x)->content)

enum					e_lists
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
	_init_talk,
	_lists_nb
};

enum					e_textures
{
	_tex_grass,
	_tex_plant,
	_tex_zepp,
	_tex_egg,
	_tex_totem,
	_ta,
	_tb,
	_tc,
	_td,
	_te,
	_tf,
	_tg,
	_th,
	_ti,
	_tj,
	_tk,
	_tl,
	_tm,
	_tn,
	_to,
	_tp,
	_tq,
	_tr,
	_ts,
	_tt,
	_tu,
	_tv,
	_tw,
	_tx,
	_ty,
	_tz,
	_tA,
	_tB,
	_tC,
	_tD,
	_tE,
	_tF,
	_tG,
	_tH,
	_tI,
	_tJ,
	_tK,
	_tL,
	_tM,
	_tN,
	_tO,
	_tP,
	_tQ,
	_tR,
	_tS,
	_tT,
	_tU,
	_tV,
	_tW,
	_tX,
	_tY,
	_tZ,
	_t0,
	_t1,
	_t2,
	_t3,
	_t4,
	_t5,
	_t6,
	_t7,
	_t8,
	_t9,
	_tex_nb
};

enum					e_models
{
	_mod_stone,
	_mod_plant,
	_mod_owl1,
	_mod_owl2,
	_mod_owl3,
	_mod_egg,
	_mod_totem,
	_mod_talk,
	_mod_nb
};

enum					e_vbos
{
	_vbo_vrtx,
	_vbo_nrms,
	_vbo_texp,
	_vbo_indx,
	_vbo_nb
};

enum					e_coord
{
	_x,
	_y,
	_z
};

enum					e_colors
{
	_r,
	_g,
	_b
};

typedef unsigned char	t_uchar;

typedef struct			s_square
{
	char		tile;
	t_uchar		grid[CASE_MAX_ITEMS];
	int			itms[_itm_nb];
	t_list		*anims;
	t_list		*mobs;
	t_list		*egg;
}						t_square;

typedef struct s_anim	t_anim;
typedef struct s_move	t_move;

struct					s_move
{
	int			frame;
	int			maxframe;
	GLfloat		pos[3];
	GLfloat		dir[3];
	void		(*fct)(t_move *);
};

typedef struct			s_rot
{
	int			frames;
	GLfloat		vec[3];
	GLfloat		angle;
	GLfloat		rot;
}						t_rot;

typedef struct			s_item
{
	GLuint		list;
	GLuint		vbo;
	t_anim		*anim;
	void		(*fct)(struct s_item *);
}						t_item;

typedef struct			s_mob
{
	int			id;
	t_move		*move;
	t_rot		*rot;
	t_anim		*anim;
}						t_mob;

typedef struct			s_egg
{
	int			id;
	int			x;
	int			y;
	char		*team;
}						t_egg;

typedef struct			s_npc
{
	int			x;
	int			y;
	t_inv		inv;
	int			dir;
	int			id;
	int			lvl;
	t_square	*sq;
	char		*team;
}						t_npc;

struct					s_anim
{
	int			frame;
	int			maxframe;
	void		(*fct)(t_anim *);
	char		dead;
};

typedef struct			s_env
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
	int			curr_npc;
	GLfloat		teamcol[TEAM_COLORS][3];
}						t_env;

typedef struct			s_pol
{
	char				c;
	int					n;
}						t_pol;

t_env					*g_env;

#endif
