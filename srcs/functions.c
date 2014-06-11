/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 15:35:59 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/06 18:48:50 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <common.h>

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

char		*type_to_str(int type)
{
	if (type == _food)
		return ("nourriture");
	else if (type == _sibur)
		return ("sibur");
	else if (type == _linemate)
		return ("linemate");
	else if (type == _phiras)
		return ("phiras");
	else if (type == _deraumere)
		return ("deraumere");
	else if (type == _thystame)
		return ("thystame");
	else if (type == _mendiane)
		return ("mendiane");
	return ("(error)");
}
