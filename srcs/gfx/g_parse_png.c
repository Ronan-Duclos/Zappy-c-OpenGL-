/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_png.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/10 21:08:23 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/27 01:49:13 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include "png2.h"
#include "png.h"
#include "common.h"

void		png_my_ass(png_structp *ppng, png_infop *pinfo, png_infop *pend,
	t_png_header infos)
{
	png_byte		*data;
	png_bytep		*row_pointers;
	uint32_t		i;

	data = (png_byte *)XV(NULL, malloc(infos.wid * infos.hgt * sizeof(int)),
						"malloc");
	row_pointers = (png_bytep *)XV(NULL, malloc(infos.hgt * sizeof(png_bytep)),
								"malloc");
	i = 0;
	while (i < infos.hgt)
	{
		row_pointers[i] = data + i * (infos.wid * sizeof(uint32_t));
		i++;
	}
	png_read_image(*ppng, row_pointers);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, infos.wid, infos.hgt, 1,
				GL_RGBA, GL_UNSIGNED_BYTE, data);
	png_destroy_read_struct(ppng, pinfo, pend);
	free(data);
	free(row_pointers);
}

FILE		*load_png(char *name)
{
	png_byte		head[8];
	FILE			*fd;

	if (!(fd = fopen(name, "rb")))
	{
		printf("This file does not want to open: %s\n", name);
		return (0);
	}
	if (!fread(head, 1, 8, fd))
	{
		printf("This file does contains shit: %s\n", name);
		return (0);
	}
	if (png_sig_cmp((unsigned char *)head, 0, 8))
	{
		printf("png error: %s is not a PNG file !!!1!\n", name);
	}
	return (fd);
}

static int	init_png(png_structp *ppng, png_infop *pinfo, png_infop *pend)
{
	if (!(*ppng = png_create_read_struct(PNG_LIBPNG_VER_STRING,
										NULL, NULL, NULL)))
	{
		fprintf(stderr, "error: png_create_read_struct failed.\n");
		return (1);
	}
	if (!(*pinfo = png_create_info_struct(*ppng)))
	{
		png_destroy_read_struct(ppng, NULL, NULL);
		fprintf(stderr, "error: png_create_info_struct failed.\n");
		return (1);
	}
	if (!(*pend = png_create_info_struct(*ppng)))
	{
		png_destroy_read_struct(ppng, pinfo, NULL);
		fprintf(stderr, "error: png_create_info_struct failed.\n");
		return (1);
	}
	if (setjmp(png_jmpbuf(*ppng)))
	{
		fprintf(stderr, "error from libpng.\n");
		png_destroy_read_struct(ppng, pinfo, pend);
		return (1);
	}
	return (0);
}

int			fill_tex(FILE *fd)
{
	png_structp		png_ptr;
	png_infop		info_ptr;
	png_infop		end_ptr;
	t_png_header	infos;

	if (init_png(&png_ptr, &info_ptr, &end_ptr))
		return (1);
	png_init_io(png_ptr, fd);
	png_set_sig_bytes(png_ptr, 8);
	png_read_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &infos.wid, &infos.hgt, &infos.bit_dpt,
				&infos.col_type, NULL, NULL, NULL);
	png_read_update_info(png_ptr, info_ptr);
	png_my_ass(&png_ptr, &info_ptr, &end_ptr, infos);
	return (0);
}

GLuint		texture_from_png(char *name)
{
	GLuint	id;
	FILE	*fd;

	fd = load_png(name);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	fill_tex(fd);
	fclose(fd);
	return (id);
}
