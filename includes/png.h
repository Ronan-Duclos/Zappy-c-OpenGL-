/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/10 20:59:29 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/12 01:20:48 by tmielcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PNG_H
# define PNG_H

# include <GLUT/glut.h>

# define PNG_HEAD			"\x89\x50\x4E\x47\x0D\x0A\x1A\x0A"

# define PNG_IMAGE_HEADER	"IHDR"
# define PNG_PALETTE		"PLTE"
# define PNG_IMAGE_DATA		"IDAT"
# define PNG_IMAGE_END		"IEND"

# define B0(v)				((v << 24) & 0xFF000000)
# define B1(v)				((v << 8) & 0x00FF0000)
# define B2(v)				((v >> 8) & 0x0000FF00)
# define B3(v)				((v >> 24) & 0x000000FF)

# define SWAP_32BITS(v)		(B3(v) | B2(v) | B1(v) | B0(v))

# define S32(v)				SWAP_32BITS((v))

typedef struct	s_png_header
{
	int			wid;
	int			hgt;
	char		bit_dpt;
	char		col_type;
	char		compr;
	char		filtr;
	char		inter;
}				t_png_header;

typedef struct	s_png_chunk
{
	int			len;
	int			type;
}				t_png_chunk;

typedef struct	s_png
{
}				t_png;

void			*load_file_2(char *b, char **data, int *l);
GLuint			texture_from_png(char *n);

#endif
