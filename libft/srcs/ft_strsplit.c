/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 15:37:31 by caupetit          #+#    #+#             */
/*   Updated: 2014/01/13 18:38:19 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_get_line_nb(char const *s, char c)
{
	size_t	zl;

	zl = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		while (*s && *s != c)
			s++;
		if (*s)
			zl++;
	}
	if (*(s - 1) != c)
		zl++;
	return (zl);
}

static void	ft_deltab(char **tab, int nb)
{
	int		i;

	i = 0;
	while (i < nb)
	{
		ft_strdel(&tab[i]);
		i++;
	}
	ft_memdel((void **)tab);
}

static int	ft_getcnum(char const *s, int c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	size_t	zl;
	char	**s1;

	i = 0;
	zl = ft_get_line_nb(s, c);
	if (!(s1 = (char **)malloc(zl * sizeof(char *) + 1)))
		return (NULL);
	while (i < (int)zl)
	{
		s += ft_getcnum(s, c);
		j = 0;
		while (s[j] && s[j] != c)
			j++;
		if (!(s1[i] = ft_strsub(s, 0, j)))
		{
			ft_deltab(s1, i);
			return (NULL);
		}
		i++;
		s += j;
	}
	s1[i] = '\0';
	return (s1);
}
