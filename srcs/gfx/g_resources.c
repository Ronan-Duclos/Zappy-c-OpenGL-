/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_resources.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 22:20:29 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/16 22:40:01 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "png2.h"
#include "mdx.h"
#include "gfx_gl.h"

void		resources_load(t_env *env)
{
	t_mdx	mdx;

	env->maptex = texture_from_png("data/Grass.png");
	env->testex = texture_from_png("data/Plant.png");

	get_model_from_mdx("data/CrystalShard.mdx", &mdx);
	ft_vbo_from_mdx(&mdx, env->vbos[_mod_stone], env->vbosizes[_mod_stone]);
	get_model_from_mdx("data/Shimmerweed.mdx", &mdx);
	ft_vbo_from_mdx(&mdx, env->vbos[_mod_plant], env->vbosizes[_mod_plant]);
}
