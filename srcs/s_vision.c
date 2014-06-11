/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_vision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 11:57:59 by rbernand          #+#    #+#             */
/*   Updated: 2014/06/11 12:00:59 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <serveur.h>

t_inv			*get_field_vision(t_env *env, t_player *p)
{
	t_inv		*field;
	int			lvl;

	lvl = p->lvl;
	field = (t_inv *)malloc((get_vision_nb_cell(lvl) + 1) * sizeof(t_inv));

	return (field);
}
