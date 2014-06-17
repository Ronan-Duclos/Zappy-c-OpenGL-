/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 15:35:59 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/16 23:31:49 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
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
	else if (type == _player)
		return ("joueur");
	return ("(error)");
}

int			str_to_type(char *str)
{
	if (strcmp(str, "nourriture") == 0)
		return (_food);
	else if (strcmp(str, "sibur") == 0)
		return (_sibur);
	else if (strcmp(str, "linemate") == 0)
		return (_linemate);
	else if (strcmp(str, "phiras") == 0)
		return (_phiras);
	else if (strcmp(str, "deraumere") == 0)
		return (_deraumere);
	else if (strcmp(str, "thystame") == 0)
		return (_thystame);
	else if (strcmp(str, "mendiane") == 0)
		return (_mendiane);
	else if (strcmp(str, "player") == 0)
		return (_player);
	return (-1);
}
