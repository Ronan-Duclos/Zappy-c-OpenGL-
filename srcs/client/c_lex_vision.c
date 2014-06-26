/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_lex_vision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/18 18:42:23 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/26 23:37:26 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <client.h>

static void				jump_space(char *str, int *i)
{
	while (str[*i] == ' ')
	{
		if (str[*i] == 0)
			return ;
		(*i)++;
	}
}

static int				get_word(char *src, char *dest)
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

void					add_item(t_inv cell, char *word)
{
	int				type;

	if ((type = str_to_type(word)) == -1)
		return ;
	cell[type]++;
}

void					get_vision(t_env *e, char *str)
{
	int				i;
	int				j;
	int				nb_cell;
	char			word[11];

	if (e->user->player.ia.view)
		free(e->user->player.ia.view);
	nb_cell = get_vision_nb_cell(e->user->player.ia.lvl);
	e->user->player.ia.view = XV(NULL, (malloc(sizeof(t_inv) * nb_cell)), "M");
	bzero(e->user->player.ia.view, sizeof(t_inv) * nb_cell);
	i = 0;
	j = 1;
	while (i < nb_cell)
	{
		bzero(word, 11);
		jump_space(str, &j);
		j += get_word(str + j, word);
		add_item(e->user->player.ia.view[i], word);
		jump_space(str, &j);
		if (str[j] == ',' && j++)
			i++;
		if (str[j] == '}')
			break ;
	}
}
