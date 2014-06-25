/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_circle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/07 17:01:39 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/25 14:41:55 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"

int				verify_end(t_buf *buf, int i)
{
	if ((buf->head2 + i) >= buf->end)
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

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			buf->nb_cmd++;
		buf->head2[j] = str[i];
		j = verify_end(buf, j);
		i++;
	}
	if (type == 1)
	{
		buf->head2[j] = '\n';
		j = verify_end(buf, j);
		buf->nb_cmd++;
	}
	buf->head2 = buf->head2 + j;
}

void			char_to_bc(t_buf *buf, char c)
{
	int	i;

	buf->head2[0] = c;
	i = verify_end(buf, 1);
	buf->head2 = buf->head2 + i;
}

void			bc_to_tmp(t_buf *buf, char *tmp)
{
	int		j;

	j = -1;
	while (buf->nb_cmd != 0)
	{
		if (*buf->head != '\0')
			tmp[++j] = *buf->head;
		*buf->head = '\0';
		if (tmp[j] == '\n')
			buf->nb_cmd--;
		if (buf->head >= buf->end)
			buf->head = buf->start;
		else
			buf->head++;
	}
	tmp[++j] = '\0';
}
