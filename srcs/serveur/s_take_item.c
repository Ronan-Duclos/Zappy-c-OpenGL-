/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_take_item.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmansour <dmansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 18:24:39 by dmansour          #+#    #+#             */
/*   Updated: 2014/06/12 18:34:42 by dmansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <serveur.h>
#include <common.h>

t_ponf_cmd		g_tab[NBR_CMD];

char		*get_item_name(t_env *e, int cs)
{
	return (e->users[cs]->player.acts[e->users[cs]->player.cur_aread].cmd);
}

void			take_item(t_env *e, int cs)
{
	printf("hxdfgjhdxgjhfgvxsdjh g           %s\n", get_item_name(e, cs));
}
