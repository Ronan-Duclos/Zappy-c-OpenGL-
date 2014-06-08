/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/22 01:33:40 by tmielcza          #+#    #+#             */
/*   Updated: 2014/06/06 21:47:17 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "irc.h"

#include <stdio.h>

static int	build_cmd(t_buf *buf, char *cmd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((i < 1 || cmd[i - 1] != '\n') && i < buf->size)
	{
		cmd[i] = buf->head[j];
		if (buf->head + j == buf->end)
		{
			buf->head = buf->buf;
			j = -1;
		}
		i++;
		j++;
	}
	buf->head += j;
	buf->size -= i;
	return (i);
}

void		fill_buf(t_buf *buf, char *str, int slen)
{
	int		n;
	int		start;
	int		i;

	i = 0;
	start = buf->tail - buf->buf;
	n = MIN(slen, BC_SIZE - buf->size);
	while (i < n)
	{
		buf->buf[(start + i) % BC_SIZE] = str[i];
		i++;
	}
	buf->size += n;
	buf->tail = buf->buf + (start + i) % BC_SIZE;
	if (buf->size == BC_SIZE)
		buf->buf[(buf->tail - buf->buf + BC_SIZE- 1) % BC_SIZE] = '\n';
}
