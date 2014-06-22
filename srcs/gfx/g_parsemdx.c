/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_parsemdx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 22:32:44 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/22 00:29:52 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "gfx_gl.h"
#include "mdx.h"

static int	data_type(int type)
{
	int				i;
	int				*test;
	static char		tab[][4] = {

	MDX_VERTEX,
	MDX_NORMALS,
	MDX_FACE_TYPE_GROUP,
	MDX_FACE_GROUP,
	MDX_FACE,
	MDX_VERTEX_GROUP,
	MDX_MATRIX_GROUP,
	MDX_MATRIX_INDEXES};
	i = 0;
	test = (int *)tab;
	while (test[i] != type)
		i++;
	if (i == _vrtx || i == _nrms)
		return (3 * sizeof(float));
	if (i == _ptyp || i == _mtgc || i == _mats)
		return (sizeof(uint32_t));
	if (i == _pvtx)
		return (sizeof(uint16_t));
	if (i == _gndx)
		return (sizeof(char));
	return (sizeof(uint32_t));
}

static void	get_model_texture(t_mdxchunk *chunk, t_geoset geos)
{
	t_mdxchunk	*header;
	char		*tmp;

	tmp = (char *)chunk + 3 * sizeof(uint32_t);
	tmp += 7 * sizeof(float);
	printf("extends = %d\n", *(int *)tmp);
	header = (t_mdxchunk *)(tmp + *(int *)tmp * sizeof(float) * 7 + sizeof(uint32_t));
	header++;
	geos[_uvbs].nb = header->size;
	geos[_uvbs].data = header + 1;
	printf("%4.4s size = %d\n", (char *)header, header->size);
}

static uint32_t	get_model_geoset(t_mdxchunk *chunk, t_list **geos)
{
	t_mdxchunk	*header;
	int			jump;
	int			i;
	uint32_t	size;
	t_geoset	*new;

	i = 0;
	new = (t_geoset *)XV(NULL, malloc(sizeof(t_geoset)), "malloc");
	header = (t_mdxchunk *)((char *)chunk + sizeof(*chunk));
	size = *(uint32_t *)header;
	printf("GEOSET CHUNK size = %d\n", (int)size);
	header = (t_mdxchunk *)((uint32_t *)header + 1);
	while (header - chunk < chunk->size && header->size > 0)
	{
		printf("%4.4s size = %d\n", (char *)header, header->size);
		jump = header->size * data_type(header->tag) + sizeof(*header);
		(*new)[i].nb = header->size;
		(*new)[i].data = header + 1;
		if (header->tag == *(uint32_t *)MDX_MATRIX_INDEXES)
		{
			get_model_texture((t_mdxchunk *)((char *)header + jump), *new);
			break ;
		}
		header = (t_mdxchunk *)((char *)header + jump);
		i++;
	}
	add_link_end(geos, new);
	return (size);
}

int			get_model_from_mdx(char *name, t_mdx *model)
{
	char		*file;
	t_mdxchunk	*header;
	uint32_t	total;

	printf("MODEL : %s -----\n", name);
	if (!(file = load_file(name)))
	{
		printf("Error load_file()\n");
		exit(0);
	}
	model->model = file;
	model->geosets = NULL;
	header = (t_mdxchunk *)file;
	header = (t_mdxchunk *)(file + sizeof(uint32_t));
	while (header->tag != *(uint32_t *)MDX_GEOSET)
	{
		printf("%4.4s size = %d\n", (char *)header, header->size);
		header = (t_mdxchunk *)((char *)(header + 1) + header->size);
	}
	printf("%4.4s size = %d\n", (char *)header, header->size);
	total = 0;
	while (total < header->size)
		total += get_model_geoset((t_mdxchunk *)((char *)header + total),
								&model->geosets);
	printf("-------------------\n");
	return (0);
}
