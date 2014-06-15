/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_png.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/10 21:08:23 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/14 22:21:56 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include "png.h"

char		*load_png(char *name, int *rlen)
{
	char			*data;
	int				len;

	data = NULL;
	load_file_2(name, &data, &len);
	if (!data)
	{
		printf("Erreur suce ma bite\n");
	}
	else if (*(uint64_t *)data != *(uint64_t *)PNG_HEAD)
	{
		printf("Error sale bouffon\n");
		munmap(data, len);
	}
	*rlen = len;
	return (data);
}


int			fill_tex(char *data)
{
	t_png_chunk		*chunk;
	t_png_header	*hd;
	char			*img;
	char			*queue;
	uint32_t		test;
	char			boule;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	chunk = (t_png_chunk *)(data + 8);
	boule = 0;
	while (chunk->type != *(int *)PNG_IMAGE_END)
	{
		test = 0;
		printf("chunk = %4.4s, size = %d\n", (char *)&chunk->type, SWAP_32BITS(chunk->len));
		if (chunk->type == *(int *)PNG_IMAGE_HEADER)
		{
			printf("TEST\n");
			hd = (t_png_header *)(chunk + 1);
			if (hd->bit_dpt != 8 || hd->col_type != 6 || hd->compr || hd->filtr
				|| hd->inter)
			{
				printf("png format not supported...");
				return (1);
			}
			printf("wid %d hgt %d bit_dpt %d\n", S32(hd->wid), SWAP_32BITS(hd->hgt), hd->bit_dpt);
			printf("size = %d\n", S32(hd->wid) * S32(hd->hgt) * 4);
			if (!(img = (char *)malloc(S32(hd->wid) * S32(hd->hgt) * 4)))
				printf("Suck it\n");
			queue = img;
		}
		if (chunk->type == *(int *)PNG_IMAGE_DATA && S32(chunk->len) > 400)
		{
				if (!boule)
				{
					test += 8;
					boule = 1;
				}
				else
				{
					printf("HELUTSUUUU\n");
					test += 16 * 4 - 1;
				}
			printf("len = %d\n", S32(chunk->len));
			while (test < S32(chunk->len))
			{
				memcpy(queue, (char *)chunk + sizeof(*chunk) + test, 512 * 4);
				test += 512 * 4 + 1;
				printf("test = %d\n", test - (test % (512 * 4)) / (512 * 4) % 16);
				if ((test - (test % (512 * 4))) / (512 * 4) % 16 == 0)
				{
					printf("TAGGLE\n");
					test += 1;
				}
				queue += 512 * 4;
			}
		}
		chunk = (t_png_chunk *)((char *)chunk + SWAP_32BITS(chunk->len) + 4);
		chunk += 1;
	}
	printf("wid = %d, hgt = %d\n", S32(hd->wid), S32(hd->hgt));
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, S32(hd->wid), S32(hd->hgt), 1, GL_RGBA, GL_UNSIGNED_BYTE, img);
	return (0);
}

GLuint		texture_from_png(char *name)
{
	GLuint	id;
	char	*data;
	int		len;

	data = load_png(name, &len);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	fill_tex(data);
	munmap(data, len);
	return (id);
}
