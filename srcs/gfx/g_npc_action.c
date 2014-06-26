/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_npc_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 02:15:40 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/26 17:56:26 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "gfx_gl.h"

void		add_mob(int npc, int x, int y, enum e_dir direc)
{
	static GLfloat	dir[3] = {0.0, 0.0, 0.0};
	static GLfloat	vec[3] = {0.0, 0.0, 1.0};
	GLfloat			pos[3];
	t_move			*move;
	t_rot			*rot;
	t_anim			*anim;
	t_square		*sq;
	t_mob			*mob;

	set_vecf(pos, (float)x * 2, 0.0, (float)y * 2);
	anim = new_anim(rand() % 360, 360, anim_mob);
	move = new_move(0, 0, pos, dir);
	rot = new_rot(0, vec, 90 * direc, 0);
	mob = new_mob(anim, move, rot, npc);
	sq = g_env->sq + x + y * g_env->mapw;
	g_env->npc[npc].sq = sq;
	sq->mobs = new_link(sq->mobs, mob);
}

/*
**	Moves a player npc from his current position to (x,y) and
**	sets his orientation to dir. Of course, inits animations
**	in order to reflect those transformations.
*/
void		move_mob(int npc, int x, int y, enum e_dir dir)
{
	t_npc	*player;
	t_list	**mob;

	mob = find_mob(npc);
	player = g_env->npc + npc;
	player->sq = &g_env->sq[x + y * g_env->mapw];
	move_init(((t_mob *)(*mob)->content)->move, x, 0, y);
	((t_mob *)(*mob)->content)->move->fct = anim_move;
	rot_init(((t_mob *)(*mob)->content)->rot, dir);
	if (!is_in_list(*mob, player->sq->mobs))
		switch_link(mob, &player->sq->mobs);
}

void		kill_mob(int npc)
{
	t_list	**mob;

	mob = find_mob(npc);
	del_link(mob, del_mob);
}

void		lower_mob(int npc)
{
	t_list	**mob;
	t_npc	*p;

	mob = find_mob(npc);
	p = g_env->npc + npc;
	move_init(((t_mob *)(*mob)->content)->move, p->x, -1, p->y);
	((t_mob *)(*mob)->content)->move->fct = anim_move2;
}

void		broadcast(int npc)
{
	t_npc	*p;
	t_anim	*a;
	t_item	*item;
	t_list	**anims;

	p = g_env->npc + npc;
	a = new_anim(0, T_BROADCAST * FPS / g_env->time, anim_rock);
	item = new_item(g_env->lists[_init_talk], _mod_talk, a, display_any);
	anims = &g_env->sq[p->x + p->y * g_env->mapw].anims;
	*anims = new_link(*anims, item);
}
