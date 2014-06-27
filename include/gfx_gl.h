/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_gl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 22:15:42 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/27 06:51:53 by dmansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_GL_H
# define GFX_GL_H

# include <GLUT/glut.h>
# include "mdx.h"
# include "common.h"
# include "libft.h"
# include "gfx_protos.h"

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
void			display_rect(int x, int y, int lettre);
void			display_words(float x, float y, char *str);

/*
**	g_input.c
*/
void			speckeyup(int key, int xmouse, int ymouse);
void			speckey(int key, int xmouse, int ymouse);
void			keykey(unsigned char key, int xmouse, int ymouse);
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
void			map_intersection(GLdouble *i, GLdouble *a, GLdouble *b);
void			set_vecf(GLfloat vec[3], GLfloat x, GLfloat y, GLfloat z);
void			getdir(GLdouble o[3], GLdouble dir[3]);
void			getdirf(GLfloat o[3], GLfloat dir[3]);

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
void			display_egg(int i);
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
void			del_item(void *item);
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
void			broadcast(int npc);

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

/*
**	g_display_hud.c
*/
void			display_footer(void);

#endif
