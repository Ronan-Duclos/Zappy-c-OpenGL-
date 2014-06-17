/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_vbo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 22:25:13 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/16 22:09:12 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mdx.h"
#include "gfx_gl.h"

void	ft_vbo_from_mdx(t_mdx *mdx, GLuint *vbos, int *vbosizes)
{
	glGenBuffers(4, vbos);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[_vbo_vrtx]);
	glBufferData(GL_ARRAY_BUFFER, mdx->chunks[_vrtx].nb * sizeof(float) * 3,
			mdx->chunks[_vrtx].data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[_vbo_nrms]);
	glBufferData(GL_ARRAY_BUFFER, mdx->chunks[_nrms].nb * sizeof(float) * 3,
			mdx->chunks[_nrms].data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[_vbo_texp]);
	glBufferData(GL_ARRAY_BUFFER, mdx->chunks[_uvbs].nb * sizeof(float) * 2,
			mdx->chunks[_uvbs].data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[_vbo_indx]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			mdx->chunks[_pvtx].nb * sizeof(uint16_t) * 3,
			mdx->chunks[_pvtx].data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	vbosizes[_vbo_vrtx] = mdx->chunks[_vrtx].nb;
	vbosizes[_vbo_nrms] = mdx->chunks[_nrms].nb;
	vbosizes[_vbo_texp] = mdx->chunks[_uvbs].nb;
	vbosizes[_vbo_indx] = mdx->chunks[_pvtx].nb;
}
