/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 18:17:50 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/27 06:00:28 by dmansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/resource.h>
#include <strings.h>
#include "gfx_gl.h"

static void	team_colors_init(GLfloat teamcol[TEAM_COLORS][3])
{
	int		i;
	int		j;
	int		k;
	GLfloat	tmp;

	i = 0;
	j = -1;
	while (i / 3 < TEAM_COLORS)
	{
		teamcol[i / 3][i % 3] = 0.25 * (i % 5);
		teamcol[i / 3 + 1][(i + 1) % 3] = 0.25 * ((i + 1) / 5 % 5);
		teamcol[i / 3 + 2][(i + 2) % 3] = 0.25 * ((i + 1) / 5 / 5);
		i += 3;
	}
	while (++j < TEAM_COLORS)
	{
		i = -1;
		k = rand() % TEAM_COLORS;
		while (++i < 3)
		{
			tmp = teamcol[j][i];
			teamcol[j][i] = teamcol[k][i];
			teamcol[k][i] = tmp;
		}
	}
}

static void	lists_init(t_env *env)
{
	int		i;
	GLuint	val;

	(void)env;
	i = 0;
	val = glGenLists(_lists_nb);
	while (i < _lists_nb)
	{
		g_env->lists[i] = val + i;
		i++;
	}
}

static void	names_init(t_env *env)
{
	struct rlimit	rlp;
	int				j;

	X(-1, getrlimit(RLIMIT_NOFILE, &rlp), "getrlimit");
	j = rlp.rlim_cur;
	env->max_teams = j;
	env->tnames = (char **)XV(NULL, malloc(sizeof(char *) * j), "names_init");
	bzero(env->tnames, sizeof(char *) * j);
}

static void	npcs_init(t_env *env)
{
	env->npc = (t_npc *)XV(NULL, malloc(sizeof(t_npc) * NPCS_MAX), "mpcs_init");
	bzero(env->npc, sizeof(t_npc) * NPCS_MAX);
}

void		env_init(t_env *env)
{
	g_env = env;
	bzero(env, sizeof(*env));
	env->curr_npc = 0;
	env->selectcase = -1;
	env->camtrans[0] = -0.5;
	env->camtrans[1] = -10.1;
	env->camtrans[2] = -30.0;
	names_init(env);
	npcs_init(env);
	lists_init(env);
	list_item_init(env);
	list_white_init();
	list_red_init();
	list_blue_init();
	list_green_init();
	list_yellow_init();
	list_pink_init();
	list_cyan_init();
	list_highlight_init();
	team_colors_init(g_env->teamcol);
}
