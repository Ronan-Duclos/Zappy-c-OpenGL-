/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_circle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/07 17:01:39 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/07 23:06:50 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"

void			init_bc(t_buf *buf)
{
	ft_bzero(buf->start, BC_SIZE);
	buf->end = buf->start + BC_SIZE2;
	buf->head = buf->start;
	buf->head2 = buf->start;
	buf->tail = buf->start;
}

int				verify_bsn(t_buf *buf)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = buf->head;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == '\n')
			return (1);
		if (tmp + i == buf->end)
		{
			tmp = buf->start;
			i = 0;
		}
		else
			i++;
	}
	return (0);
}

int				verify_end(t_buf *buf, int i)
{
	if (buf->head2 + i == buf->end)
	{
		buf->head2 = buf->start;
		i = 0;
	}
	else
		i++;
	return (i);
}

void			tmp_to_bc(t_buf *buf, char *str, int type)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[++i] != '\0')
	{
		buf->head2[j] = str[i];
		j = verify_end(buf, j);
	}
	if (type == 1)
	{
		buf->head2[j] = '\n';
		j = verify_end(buf, j);
		buf->head2[j] = '\0';
	}
	else
		buf->head2[j] = ' ';
	j = verify_end(buf, j);
	buf->head2 = buf->head2 + j;
}

void			char_tmp_to_c(t_buf *buf, char c)
{
	int	i;

	buf->head2[0] = c;
	buf->tail = buf->head2;
	i = verify_end(buf, 1);
	buf->head2 = buf->head2 + i;
}

static void		bc_to_tmp_end(t_buf *buf, int i)
{
	if (buf->head + i + 1 != buf->end)
		if (buf->head + i + 2 != buf->end)
			buf->head = buf->head + i + 2;
		else
			buf->head = buf->start;
	else
		buf->head = buf->start + 1;
}

void			bc_to_tmp(t_buf *buf, char *tmp)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (buf->head[i] != '\n')
	{
		tmp[++j] = buf->head[i];
		buf->head[i] = '\0';
		if (buf->head + i == buf->end)
		{
			buf->head = buf->start;
			i = 0;
		}
		else
			i++;
	}
	tmp[++j] = '\n';
	tmp[++j] = '\0';
	bc_to_tmp_end(buf, i);
}
