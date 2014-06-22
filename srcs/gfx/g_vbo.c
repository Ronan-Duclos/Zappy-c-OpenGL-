/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_vbo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 22:25:13 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/21 23:51:37 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mdx.h"
#include "gfx_gl.h"

void	ft_vbo_from_mdx(t_geoset geos, GLuint *vbos, int *vbosizes)
{
	glGenBuffers(_vbo_nb, vbos);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[_vbo_vrtx]);
	glBufferData(GL_ARRAY_BUFFER, geos[_vrtx].nb * sizeof(float) * 3,
			geos[_vrtx].data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[_vbo_nrms]);
	glBufferData(GL_ARRAY_BUFFER, geos[_nrms].nb * sizeof(float) * 3,
			geos[_nrms].data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[_vbo_texp]);
	glBufferData(GL_ARRAY_BUFFER, geos[_uvbs].nb * sizeof(float) * 2,
			geos[_uvbs].data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[_vbo_indx]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			geos[_pvtx].nb * sizeof(uint16_t) * 3,
			geos[_pvtx].data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	vbosizes[_vbo_vrtx] = geos[_vrtx].nb;
	vbosizes[_vbo_nrms] = geos[_nrms].nb;
	vbosizes[_vbo_texp] = geos[_uvbs].nb;
	vbosizes[_vbo_indx] = geos[_pvtx].nb;
}
