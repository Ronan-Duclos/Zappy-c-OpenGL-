/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_parsemdx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 22:32:44 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/21 16:07:16 by tmielcza         ###   ########.fr       */
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

static void	get_model_texture(t_mdxchunk *chunk, t_mdx *model)
{
	t_mdxchunk	*header;
	char		*tmp;

	tmp = (char *)chunk + 3 * sizeof(uint32_t);
	tmp += 7 * sizeof(float);
	printf("extends = %d\n", *(int *)tmp);
	header = (t_mdxchunk *)(tmp + *(int *)tmp * sizeof(float) * 7 + sizeof(uint32_t));
	printf("%4.4s size = %d\n", (char *)header, header->size);
	header++;
	model->chunks[_uvbs].nb = header->size;
	model->chunks[_uvbs].data = header + 1;
}

static void	get_model_geoset(t_mdxchunk *chunk, t_mdx *model)
{
	t_mdxchunk	*header;
	int			jump;
	int			i;

	i = 0;
	printf("GEOSET \n");
	header = (t_mdxchunk *)((char *)chunk + sizeof(*chunk) + sizeof(uint32_t));
	while (header - chunk < chunk->size && header->size > 0)
	{
		printf("%4.4s size = %d\n", (char *)header, header->size);
		jump = header->size * data_type(header->tag) + sizeof(*header);
		model->chunks[i].nb = header->size;
		model->chunks[i].data = header + 1;
		if (header->tag == *(uint32_t *)MDX_MATRIX_INDEXES)
		{
			get_model_texture((t_mdxchunk *)((char *)header + jump), model);
			break ;
		}
		header = (t_mdxchunk *)((char *)header + jump);
		i++;
	}
}

int			get_model_from_mdx(char *name, t_mdx *model)
{
	char		*file;
	t_mdxchunk	*header;

	if (!(file = load_file(name)))
	{
		printf("Error load_file()\n");
		exit(0);
	}
	model->model = file;
	header = (t_mdxchunk *)file;
	header = (t_mdxchunk *)(file + sizeof(uint32_t));
	while (header->tag != *(uint32_t *)MDX_GEOSET)
	{
		printf("%4.4s size = %d\n", (char *)header, header->size);
		header = (t_mdxchunk *)((char *)(header + 1) + header->size);
	}
	get_model_geoset(header, model);
	return (0);
}
