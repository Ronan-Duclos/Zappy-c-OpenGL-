/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_circle2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/25 14:40:31 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/25 14:48:17 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"

void			display_bc(t_buf *bc)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = bc->head;
	printf("Display TMP_TO_BC : \n");
	while (tmp[i] != '\n')
	{
		ft_putchar(tmp[i]);
		if (tmp + i == bc->end)
			tmp = bc->start;
		else
			i++;
	}
	ft_putchar('\n');
}

void			init_bc(t_buf *buf)
{
	ft_bzero(buf->start, BC_SIZE + 1);
	buf->end = buf->start + BC_SIZE;
	buf->head = buf->start;
	buf->head2 = buf->start;
	buf->nb_cmd = 0;
}

int				verify_bsn(t_buf *buf)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = buf->head;
	while ((tmp + i) != buf->head2)
	{
		if (tmp[i] == '\n')
			return (1);
		if ((tmp + i) == buf->end)
		{
			tmp = buf->start;
			i = 0;
		}
		else
			i++;
	}
	return (0);
}
