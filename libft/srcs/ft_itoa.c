/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 15:39:03 by caupetit          #+#    #+#             */
/*   Updated: 2014/03/08 22:26:48 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getsize(int n)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n / 10 > 0)
	{
		n = n / 10;
		i++;
	}
	return (++i);
}

static char	*ft_reverse(char *s)
{
	char	*s1;
	int		zs;
	int		i;

	i = 0;
	zs = ft_strlen(s);
	s1 = ft_strdup(s);
	if (*s == '-')
		i++;
	while (s[i])
	{
		s[i] = s1[zs - 1];
		i++;
		zs--;
	}
	ft_strdel(&s1);
	return (s);
}

char		*ft_itoa(int n)
{
	char	*s;
	size_t	z;
	int		i;

	i = 0;
	z = ft_getsize(n);
	s = ft_strnew(ft_getsize(n));
	if (!s)
		return (NULL);
	if (n == -2147483648)
		return ("-2147483648");
	if (n < 0)
	{
		s[i++] = '-';
		n *= -1;
	}
	while (i < (int)z)
	{
		s[i++] = n % 10 + '0';
		n = n / 10;
	}
	s[++i] = n % 10 + '0';
	s = ft_reverse(s);
	return (s);
}
