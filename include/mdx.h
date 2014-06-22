/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mdx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 17:05:50 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/21 23:54:38 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MDX_H
# define MDX_H

# include <stdint.h>
# include "libft.h"

# define MDX_VERSION			"VERS"
# define MDX_MODEL				"MODL"
# define MDX_SEQUENCE			"SEQS"
# define MDX_GLOB_SEQUENCE		"GLBS"
# define MDX_TEXTURES			"TEXS"
# define MDX_TEXTURES_ANIM		"TXAN"
# define MDX_GEOSET				"GEOS"
# define MDX_GEOSET_ANIM		"GEOA"
# define MDX_BONE				"BONE"
# define MDX_LIGHT				"LITE"
# define MDX_HELPER				"HELP"
# define MDX_ATTACHEMENT		"ATCH"
# define MDX_PIVOT_POINT		"PIVT"
# define MDX_PARTICLE_EMMIT		"PREM"
# define MDX_PARTICLE_EMMIT2	"PRE2"
# define MDX_RIBBON_EMMIT		"RIBB"
# define MDX_EVENT				"EVTS"
# define MDX_CAMERA				"CAMS"
# define MDX_COLLISION			"CLID"

# define MDX_VERTEX				"VRTX"
# define MDX_NORMALS			"NRMS"
# define MDX_FACE_TYPE_GROUP	"PTYP"
# define MDX_FACE_GROUP			"PCNT"
# define MDX_FACE				"PVTX"
# define MDX_VERTEX_GROUP		"GNDX"
# define MDX_MATRIX_GROUP		"MTGC"
# define MDX_MATRIX_INDEXES		"MATS"
# define MDX_UVBS				"UVBS"

enum			e_mdxchunks
{
	_vrtx,
	_nrms,
	_ptyp,
	_pcnt,
	_pvtx,
	_gndx,
	_mtgc,
	_mats,
	_uvbs
};

typedef struct	s_mdxchunk
{
	uint32_t	tag;
	uint32_t	size;
}				t_mdxchunk;

typedef struct	s_modchunk
{
	uint32_t	nb;
	void		*data;
}				t_modchunk;

typedef struct	s_mdx
{
	void		*model;
	t_list		*geosets;
}				t_mdx;

typedef	t_modchunk	t_geoset[9];

t_mdx			g_mdx; // VIEILLE GLOBALE DEGUEULASSE

/*
**	g_parsemdx.c (3 statics)
*/
int				get_model_from_mdx(char *name, t_mdx *model);

#endif
