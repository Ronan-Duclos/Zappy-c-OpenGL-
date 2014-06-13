/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 11:17:45 by rbernand          #+#    #+#             */
/*   Updated: 2014/01/26 18:57:05 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

void		ft_tabdel(char ***tab)
{
	unsigned int	i;

	i = -1;
	while ((*tab)[++i])
		ft_strdel(&((*tab)[i]));
	free(*tab);
	*tab = NULL;
}
