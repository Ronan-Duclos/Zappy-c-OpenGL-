/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 15:35:59 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/03 15:39:40 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int			rand_int(int min, int max)
{
	return (min + rand() % max);
}

int			get_vision_nb_cell(int level)
{
	if (level == 0)
		return (1);
	return (get_vision_nb_cell(level - 1) + (2 * level + 1));
}
