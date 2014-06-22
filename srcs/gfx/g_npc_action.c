/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_npc_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 02:15:40 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/21 19:41:48 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "gfx_gl.h"

t_mob		*new_mob(t_anim *anim, t_move *move, t_rot *rot, int id)
{
	t_mob	*new;

	new = (t_mob *)XV(NULL, malloc(sizeof(t_mob)), "malloc");
	new->move = move;
	new->rot = rot;
	new->anim = anim;
	new->id = id;
	return (new);
}

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
	move = new_move(0, pos, dir);
	rot = new_rot(0, vec, 90 * direc, 0);
	mob = new_mob(anim, move, rot, npc);
	sq = g_env->sq + x + y * g_env->mapw;
	g_env->npc[npc].sq = sq;
	sq->mobs = new_link(sq->mobs, mob);
}

void		move_mob(int npc, int x, int y, enum e_dir dir)
{
	t_npc	*player;
	t_list	**mob;

	mob = find_mob(npc);
	player = g_env->npc + npc;
	player->sq = &g_env->sq[x + y * g_env->mapw];
	move_init(((t_mob *)(*mob)->content)->move, x, y);
	rot_init(((t_mob *)(*mob)->content)->rot, dir);
	switch_link(mob, &g_env->sq[x + y * g_env->mapw].mobs);
}
