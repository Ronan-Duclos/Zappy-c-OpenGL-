/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 18:17:50 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/19 11:55:06 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/resource.h>
#include <strings.h>
#include "gfx_gl.h"


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
}
