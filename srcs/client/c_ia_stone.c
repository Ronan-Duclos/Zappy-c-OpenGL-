/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_ia_stone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/25 19:55:17 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/26 12:36:42 by rbernand         ###   ########.fr       */
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
	if (good1 == 1)
		return (0);
	else if (good2 == 1)
		return (1);
	else
		return (2);
}

int		i_have_stone(t_ia *ia)
{
	int			i;

	i = 0;
	while (++i < NB_STONE + 1)
	{
//		printf("in i have stone (both): type [%d] lvl [%d] tot [%d] req [%d]\n", i, ia->lvl, ia->inv[i] + ia->view[0][i], g_lvlup[ia->lvl - 1][i]);
		if (ia->inv[i] + ia->view[0][i] < g_lvlup[ia->lvl - 1][i])
			return (-1);
	}
	i = 0;
	while (++i < NB_STONE + 1)
	{
//		printf("in i have stone (ground): type [%d] lvl [%d] tot [%d] req [%d]\n", i, ia->lvl, ia->view[0][i], g_lvlup[ia->lvl - 1][i]);
		if (ia->view[0][i] < g_lvlup[ia->lvl - 1][i])
			return (1);
	}
	return (0);
}
/*

int		i_have_stone(t_ia *ia)
{
	int				i;
	static int		good_inv[7] = {1, 1, 1, 1, 1, 1, 1};
	static int		good_view[7] = {1, 1, 1, 1, 1, 1, 1};

	i = 1;  pour suivre l'enum mat
	while (i <  7)
	{
		if (ia->inv[i] < g_lvlup[ia->lvl -1][i])
			good_inv[i] = 0;
		if (ia->view[0][i] < g_lvlup[ia->lvl - 1][i])
			good_view[i] = 0;
		i++;
	}
	return (cmp_inv_view(good_view, good_inv));
}*/
