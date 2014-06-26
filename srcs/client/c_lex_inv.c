/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/18 14:47:51 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/26 23:36:15 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>
#include <stdlib.h>
#include <ctype.h>

void		jump_nbr(char *str, int *i)
{
	while (isdigit(str[*i]))
	{
		if (str[*i] == 0)
			return ;
		(*i)++;
	}
}

void		jump_space(char *str, int *i)
{
	while (str[*i] == ' ')
	{
		if (str[*i] == 0)
			return ;
		(*i)++;
	}
}

int			get_word(char *src, char *dest)
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

void		get_inventaire(t_env *e, char *str)
{
	char			word[11];
	int				type;
	int				j;
	int				i;

	i = 1;
	j = 0;
	bzero(e->user->player.ia.inv, sizeof(t_inv));
	while (j++ < 6 + 1)
	{
		jump_space(str, &i);
		i += get_word(str + i, word);
		if ((type = str_to_type(word)) == -1)
			return ;
		jump_space(str, &i);
		e->user->player.ia.inv[type] = atoi(str + i);
		jump_nbr(str, &i);
		jump_space(str, &i);
		if (str[i] == ',')
			i++;
		else if (str[i] == '}')
			return ;
	}
	return ;
}
