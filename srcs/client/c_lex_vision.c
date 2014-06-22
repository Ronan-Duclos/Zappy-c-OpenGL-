/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_lex_vision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/18 18:42:23 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/22 18:35:24 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <client.h>

static void			jump_space(char *str, int *i)
{
	while (str[*i] == ' ')
	{
		if (str[*i] == 0)
			return ;
		(*i)++;
	}
}

static int			get_word(char *src, char *dest)
{
	int			i;

	i = 0;
	while (isalpha(src[i]) && i < 11)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (i);
}

void				add_item(t_inv cell, char *word)
{
	int				type;

	if ((type = str_to_type(word)) == -1)
		return ;
	cell[type]++;
}

int					get_vision(t_inv **vis, int lvl, char *str)
{
	int				i;
	int				j;
	int				nb_cell;
	char			word[11];

	if (*vis)
		free(*vis);;
	nb_cell = get_vision_nb_cell(lvl);
	*vis = XV(NULL, (malloc(sizeof(t_inv) * (nb_cell + 1))), "malloc");
	if (*str != '{')
		return (-1);
	i = 0;
	j = 1;
	while (i < nb_cell)
	{
		bzero(word, 11);
		jump_space(str, &j);
		j += get_word(str + j, word);
		add_item((*vis)[i], word);
		jump_space(str, &j);
		if (str[j] == ',' && j++)
			i++;
		if (str[j] == '}')
			break ;
	}
	return (0);
}
/*
int				main(void)
{
	t_inv		*vis;
	char str[] = "{nourriture nourriture sibur phiras, sibur, linemate phiras, nourriture phiras phiras}";

	vis = NULL;
	get_vision(&vis, 1, str);
	int i = 0;
	while (i < 4)
	{
		int j = 0;
		while (j < 8)
		{
			printf("%d : %d\n", j, vis[i][j]);
			j++;
		}
		printf("||||||||||||||||||||||\n");
		i++;
	}
}*/
