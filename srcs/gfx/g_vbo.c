/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_vbo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 22:25:13 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/13 22:56:53 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mdx.h"
#include "gfx_gl.h"

void	ft_vbo_from_mdx(t_mdx *mdx)
{
	glGenBuffers(1, &g_env->vbo_vrtx);
	glGenBuffers(1, &g_env->vbo_nrms);
	glGenBuffers(1, &g_env->vbo_indx);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbo_vrtx);
	glBufferData(GL_ARRAY_BUFFER, mdx->chunks[_vrtx].nb * sizeof(float) * 3,
			mdx->chunks[_vrtx].data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, g_env->vbo_nrms);
	glBufferData(GL_ARRAY_BUFFER, mdx->chunks[_nrms].nb * sizeof(float) * 3,
			mdx->chunks[_nrms].data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_env->vbo_indx);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			mdx->chunks[_pvtx].nb * sizeof(uint16_t) * 3,
			mdx->chunks[_pvtx].data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
