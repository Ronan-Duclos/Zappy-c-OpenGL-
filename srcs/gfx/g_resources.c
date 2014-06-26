/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_resources.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 22:20:29 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/26 17:10:24 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "png2.h"
#include "mdx.h"
#include "gfx_gl.h"

static void	mdx_load(char *name, enum e_models mod, int geos)
{
	t_mdx	mdx;
	t_list	*geosets;
	int		i;

	i = 0;
	get_model_from_mdx(name, &mdx);
	geosets = mdx.geosets;
	while (i < geos)
	{
		geosets = geosets->next;
		i++;
	}
	ft_vbo_from_mdx(geosets->content, g_env->vbos[mod], g_env->vbosizes[mod]);
}

void		resources_load(t_env *env)
{
	env->maptex = texture_from_png("data/Grass.png");
	env->testex = texture_from_png("data/Plant.png");
	env->zepptex = texture_from_png("data/GoblinZeppelin.png");
	env->textures[_tex_egg] = texture_from_png("data/ThunderLizardEgg.png");
	env->textures[_tex_totem] = texture_from_png("data/Wards1.png");
	env->textures[_ta] = texture_from_png("data/Police/am.png");
	mdx_load("data/CrystalShard.mdx", _mod_stone, 0);
	mdx_load("data/Shimmerweed.mdx", _mod_plant, 0);
	mdx_load("data/GoblinZeppelin.mdx", _mod_owl1, 0);
	mdx_load("data/GoblinZeppelin.mdx", _mod_owl2, 1);
	mdx_load("data/GoblinZeppelin.mdx", _mod_owl3, 2);
	mdx_load("data/ThunderLizardEgg.mdx", _mod_egg, 0);
	mdx_load("data/StasisTotem.mdx", _mod_totem, 3);
	mdx_load("data/TalkToMe.mdx", _mod_talk, 0);
}
