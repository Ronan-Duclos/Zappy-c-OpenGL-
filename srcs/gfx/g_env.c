/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 18:17:50 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/15 02:22:33 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>//
#include <strings.h>
#include "gfx_gl.h"

static void	lists_init(t_env *env)
{
	int		i;
	GLuint	val;

	(void)env;
	i = 0;
	val = glGenLists(_lists_nb);
	printf("val glGenList: %d\n", val);
	while (i < _lists_nb)
	{
		g_env->lists[i] = val + i;
		i++;
	}
}

void		env_init(t_env *env)
{
	g_env = env;
	bzero(env, sizeof(*env));
	env->selectcase = -1;
	env->camtrans[0] = -0.5;
	env->camtrans[1] = -10.1;
	env->camtrans[2] = -30.0;
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
