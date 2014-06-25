/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_lex_vision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/18 18:42:23 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/25 02:46:33 by rduclos          ###   ########.fr       */
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

void					get_vision(t_env *e, char *str)
{
	int				i;
	int				j;
	int				nb_cell;
	char			word[11];

	if (e->user->player.ia.view)
		free(e->user->player.ia.view);
	nb_cell = get_vision_nb_cell(e->user->player.ia.lvl);
	e->user->player.ia.view = XV(NULL, (malloc(sizeof(t_inv) * nb_cell)), "malloc");
	bzero(e->user->player.ia.view, sizeof(t_inv) * nb_cell);
	i = 0;
	j = 1;
	while (i < nb_cell)
	{
		bzero(word, 11);
		jump_space(str, &j);
		j += get_word(str + j, word);
//		printf("word in lex : [%s]\n", word);
		add_item(e->user->player.ia.view[i], word);
//		printf("|cellule cible : %s -> %d\n", word, e->user->player.ia.view[i][str_to_type(word)] );
		jump_space(str, &j);
		if (str[j] == ',' && j++)
			i++;
		if (str[j] == '}')
			break ;
	}
//	e->user->player.ia.cur_todo = e->user->player.ia.cur_todo->next;
/*	printf("get vision end %d\n", e->user->nb_cmd);
	int a;
	a = 0;
	t_inv *b;
	while (a < get_vision_nb_cell(e->user->player.ia.lvl))
	{
		b = e->user->player.ia.view;
		int c = -1;
		while (c < 7)
		printf("%d );
		a++;
	}*/
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
