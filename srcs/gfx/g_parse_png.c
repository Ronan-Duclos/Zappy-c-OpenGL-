/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_png.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/10 21:08:23 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/15 20:57:39 by tmielcza         ###   ########.fr       */
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

int			fill_tex(FILE *fd)
{
	png_structp		png_ptr;
	png_infop		info_ptr;
	png_infop		end_ptr;
	t_png_header	infos;
	png_byte		*data;
	png_bytep		*row_pointers;
	uint32_t		i;

	if (!(png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL)))
	{
		fprintf(stderr, "error: png_create_read_struct failed.\n");
		return (1);
	}
	if (!(info_ptr = png_create_info_struct(png_ptr)))
	{
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		fprintf(stderr, "error: png_create_info_struct failed.\n");
		return (1);
	}
	if (!(end_ptr = png_create_info_struct(png_ptr)))
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fprintf(stderr, "error: png_create_info_struct failed.\n");
		return (1);
	}
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		fprintf(stderr, "error from libpng.\n");
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_ptr);
		return (1);
	}

	png_init_io(png_ptr, fd);
	png_set_sig_bytes(png_ptr, 8);
	png_read_info(png_ptr, info_ptr);

	png_get_IHDR(png_ptr, info_ptr, &infos.wid, &infos.hgt, &infos.bit_dpt,
				 &infos.col_type, NULL, NULL, NULL);

	png_read_update_info(png_ptr, info_ptr);

	data = (png_byte *)XV(NULL, malloc(infos.wid * infos.hgt * sizeof(uint32_t)), "malloc");

	row_pointers = (png_bytep *)XV(NULL, malloc(infos.hgt * sizeof(png_bytep)), "malloc");

	i = 0;
	while (i < infos.hgt)
	{
		row_pointers[i] = data + i * (infos.wid * sizeof(uint32_t));
		i++;
	}

	png_read_image(png_ptr, row_pointers);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, infos.wid, infos.hgt, 1,
				GL_RGBA, GL_UNSIGNED_BYTE, data);
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_ptr);
	free(data);
	free(row_pointers);
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
