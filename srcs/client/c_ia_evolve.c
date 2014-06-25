
#include <client.h>
#include <common.h>

static int		g_lvlup[7][8] = {
	{0, 1, 0, 0, 0, 0, 0, 1},
	{0, 1, 1, 1, 0, 0, 0, 2},
	{0, 2, 0, 1, 0, 2, 0, 2},
	{0, 1, 1, 2, 0, 1, 0, 4},
	{0, 1, 2, 1, 3, 0, 0, 4},
	{0, 1, 2, 3, 0, 1, 0, 6},
	{0, 2, 2, 2, 2, 2, 1, 6}
};

static int		g_need_stone[7] = {0, 9, 8, 10, 5, 6,  1}

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


	i = 0;
	while (++i <  7)
	{
		if (ia->inv[i] < g_lvlup[ia->lvl -1][i])
			good_inv[i] = 0;
		if (ia->view[0][i] < g_lvlup[ia->lvl - 1][i])
			good_view[i] = 0;
	}
	return (cmp_inv_view(ia));
}
