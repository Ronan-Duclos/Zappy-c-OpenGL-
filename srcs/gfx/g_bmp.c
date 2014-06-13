/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_bmp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 22:08:52 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/13 22:30:06 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "gfx_gl.h"

static GLuint	new_tex(int w, int h, char *data)
{
	GLuint	id;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h,
				 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return (id);
}

GLuint	load_bmp_tex(char *file)
{
	int				fd;
	char			*data;
	int				*offset;
	int				*size;
	GLuint			tex;

	if (!(fd = open(file, O_RDONLY)))
		return (0);
	data = (char *)malloc(14 * sizeof(char));
	if (!read(fd, data, 14))
		return (0);
	offset = (int *)(data + 10);
	size = (int *)(data + 2);
	free(data);
	data = (char *)malloc((*size - 14) * sizeof(char));
	if (!read(fd, data, *size - 14))
		return (0);
	tex = new_tex(*(int *)(data + 4), *(int *)(data + 8), &data[*offset - 14]);
	free(data);
	return (tex);
}
