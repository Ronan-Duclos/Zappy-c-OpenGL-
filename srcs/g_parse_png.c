
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_png.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/10 21:08:23 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/11 18:41:27 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "png.h"

int		load_png(char *name)
{
	char			*data;
	int				len;
	t_png_chunk		*chunk;
	t_png_header	*hd;

	data = NULL;
	load_file_2(name, &data, &len);
	if (!data)
	{
		printf("Erreur suce ma bite\n");
		return (1);
	}
	if (*(uint64_t *)data != *(uint64_t *)PNG_HEAD)
	{
		printf("Error sale bouffon\n");
		munmap(data, len);
		return (1);
	}
	chunk = (t_png_chunk *)(data + sizeof(double));
	while (chunk->type != *(int *)PNG_IMAGE_END)
	{
		printf("chunk = %4.4s, size = %d\n", (char *)&chunk->type, SWAP_32BITS(chunk->len));
		if (chunk->type == *(int *)PNG_IMAGE_HEADER)
		{
			hd = (t_png_header *)(chunk + 1);
			if (hd->bit_dpt != 8 || hd->col_type != 6 || hd->compr || hd->filtr
				|| hd->inter)
			{
				printf("png format not supported...");
				munmap(data, len);
				return (1);
			}
		}
		chunk = (t_png_chunk *)((char *)chunk + SWAP_32BITS(chunk->len) *
								sizeof(char) + sizeof(int));
		chunk += 1;
	}
	munmap(data, len);
	return (0);
}

int		texture_from_png(char *name)
{

}
