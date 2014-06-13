/* Main de test GLUT by Paul-le-poulpe */

#include <GLUT/glut.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include "gfx_gl.h"
#include "common.h"
#include "mdx.h"

/*
**	Initialisation dans la structure globale (pas d'affichage)
*/
void	ft_put_stones(char tab[7], t_square *sq)
{
	int		amount;
	int		i;
	int		sect;
	int		tmp;

	i = 0;
	tmp = 0;
	amount = tab[0] + tab[1] + tab[2] + tab[3] + tab[4] + tab[5] + tab[6];
	if (amount == 0)
		return ;
	sect = CASE_MAX_ITEMS / amount;
	while (i < amount)
	{
		while (tab[tmp] == 0)
			tmp = (tmp + 1) % 7;
		sq->grid[i * sect + (rand() % sect)] = tmp;
		tab[tmp]--;
		i++;
		tmp = (tmp + 1) % 7;
	}
}

/*
**
*/
void	test_init_map(void)
{
	int		i;
	char	tab[7];
	int		j;

	i = 0;
	g_env->sq = (t_square *)malloc(g_env->maph * g_env->mapw * sizeof(t_square));
	memset(g_env->sq, -1, g_env->mapw * g_env->maph * sizeof(t_square)); // NON
	while (i / g_env->mapw < g_env->maph)
	{
		tab[0] = rand() % 5;
		tab[1] = rand() % 4;
		tab[2] = rand() % 3;
		tab[3] = rand() % 2;
		tab[4] = rand() % 2;
		tab[5] = rand() % 2;
		tab[6] = rand() % 2;
		ft_put_stones(tab, &g_env->sq[i]);
		j = rand() % 8;
		g_env->sq[i].tile = j + 4 + (j / 2 * 6);
//		g_env->sq[i].tile = 10;
		i++;
	}
}

int		main(int ac, char **av)
{
	t_env	env;
	t_mdx	mdx;
	GLuint	test; /////GROSSE BITE DE MERDE

	srand(time(NULL));
	bzero(&env, sizeof(t_env));
	g_env = &env;
	env.selectcase = -1;
	if (get_params(ac, av))
		return (1);
	test_init_map();
	init();
	env.maptex = texture_from_png("data/DirtGrass.png");
//	env.maptex = ft_load_tex("data/Lords_GrassDark2.bmp");
	get_model_from_mdx("data/CrystalShard.mdx", &g_mdx);
	ft_vbo_from_mdx(&g_mdx);
	glutMainLoop();
	return (0);
}
