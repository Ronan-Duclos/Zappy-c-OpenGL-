/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_resources.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 22:20:29 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/15 21:01:55 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "png2.h"
#include "mdx.h"
#include "gfx_gl.h"

void		resources_load(t_env *env)
{
	env->maptex = texture_from_png("data/Grass.png");
//	env->maptex = load_bmp_tex("data/Lords_GrassDark2.bmp");
	get_model_from_mdx("data/CrystalShard.mdx", &g_mdx);
	ft_vbo_from_mdx(&g_mdx);
}
