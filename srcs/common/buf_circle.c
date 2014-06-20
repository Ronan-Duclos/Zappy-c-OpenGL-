/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_circle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/07 17:01:39 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/20 17:39:20 by rduclos          ###   ########.fr       */
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
	buf->end = buf->start + BC_SIZE2;
	buf->head = buf->start;
	buf->head2 = buf->start;
//	buf->tail = buf->start;
	buf->nb_cmd = 0;
}

int				verify_bsn(t_buf *buf)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = buf->head;
	while (tmp + i != buf->head2)
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
	if (buf->head2 + i== buf->end)
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
//	printf("\033[34mtmp_to_bc: %s\033[0m\n", str);
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
//	printf("\033[35mj: %d\033[0m\n", j );
//	display_bc(buf);
}

void			char_to_bc(t_buf *buf, char c)
{
	int	i;

	buf->head2[0] = c;
//	buf->tail = buf->head2;
	i = verify_end(buf, 1);
	buf->head2 = buf->head2 + i;
}
/*
static void		bc_to_tmp_end(t_buf *buf, int i)
{
	(void)i;
	if (buf->head == buf->end)
		buf->head = buf->start;
	else
		buf->head++;
}
*/
void			bc_to_tmp(t_buf *buf, char *tmp)
{
	int		j;

	j = -1;
//printf("\033[34mbc_to_tmp: %s\033[0m\n", &buf->head[i]);
//	printf("\033[34bc_to_tmp: %s\033[0m\n", tmp);
	while (buf->nb_cmd != 0)
	{
		if (*buf->head != '\0')
			tmp[++j] = *buf->head;
		*buf->head = '\0';
		if (tmp[j] == '\n')
			buf->nb_cmd--;
		if (buf->head  == buf->end)
		{
			buf->head = buf->start;
		}
		else
			buf->head++;
	}
	tmp[++j] = '\0';
//	printf("\033[35mbc_to_tmp end: %s\033[0m\n",  );
//	bc_to_tmp_end(buf, 0);
}
