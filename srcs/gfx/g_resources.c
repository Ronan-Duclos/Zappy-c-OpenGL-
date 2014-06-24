/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_resources.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 22:20:29 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/24 03:05:35 by tmielcza         ###   ########.fr       */
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
	env->zepptex = texture_from_png("data/GoblinZeppelin.png");
	env->textures[_tex_egg] = texture_from_png("data/ThunderLizardEgg.png");
	get_model_from_mdx("data/CrystalShard.mdx", &mdx);
	ft_vbo_from_mdx(mdx.geosets->content, env->vbos[_mod_stone], env->vbosizes[_mod_stone]);
	get_model_from_mdx("data/Shimmerweed.mdx", &mdx);
	ft_vbo_from_mdx(mdx.geosets->content, env->vbos[_mod_plant], env->vbosizes[_mod_plant]);
	get_model_from_mdx("data/GoblinZeppelin.mdx", &mdx);
	ft_vbo_from_mdx(mdx.geosets->content, env->vbos[_mod_owl1], env->vbosizes[_mod_owl1]);
	ft_vbo_from_mdx(mdx.geosets->next->content, env->vbos[_mod_owl2], env->vbosizes[_mod_owl2]);
	ft_vbo_from_mdx(mdx.geosets->next->next->content, env->vbos[_mod_owl3], env->vbosizes[_mod_owl3]);
	get_model_from_mdx("data/ThunderLizardEgg.mdx", &mdx);
	ft_vbo_from_mdx(mdx.geosets->content, env->vbos[_mod_egg], env->vbosizes[_mod_egg]);
}
