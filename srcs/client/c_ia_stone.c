/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_ia_stone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/25 19:55:17 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/25 20:09:24 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>
#include <global.h>

//decrementation du tableau a chaque lvl

int		i_can_evolve(t_ia *ia)
{
	if (ia->view[0][_player] > g_lvlup[ia->lvl - 1][_player])
		return (1);
	else
		return (-1);
}

int		cmp_inv_view(int good_view[7], int good_inv[7])
{
	int				good1;
	int				good2;
	int				i;

	i = 0;
	good1 = 1;
	good2 = 1;
	while (++i < 7)
	{
		if (good_view[i] == 0 && good_inv[i] == 0)
			return (-1);
		if (good_view[i] == 0)
			good1 = 0;
		if (good_inv[i] == 0)
			good2 = 0;
	}
	if (good1 == 0)
		return (0);
	else if (good2 == 0)
		return (1);
	else
		return (2);
}

int		i_have_stone(t_ia *ia)
{
	int				i;
	static int		good_inv[7] = {1, 1, 1, 1, 1, 1, 1};
	static int		good_view[7] = {1, 1, 1, 1, 1, 1, 1};

	i = 1; /* pour suivre l'enum mat*/
	while (i <  7)
	{
		if (ia->inv[i] < g_lvlup[ia->lvl -1][i])
			good_inv[i] = 0;
		if (ia->view[0][i] < g_lvlup[ia->lvl - 1][i])
			good_view[i] = 0;
		i++;
	}
	return (cmp_inv_view(good_view, good_inv));
}
