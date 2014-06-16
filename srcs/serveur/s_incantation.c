
#include <serveur.h>
#include <common.h>

void	incantation(t_env *e, int cs)
{
	int		x;
	int		y;
	int		lvl;
	int		good;
	int		i;

	x = e->users[cs]->player.x;
	y = e->users[cs]->player.y;
	lvl = e->users[cs]->player.lvl;
	good = 1;
	i = 0;
	while (++i < NB_STONE + 1)
		if (e->map[x][y].ground[i] < g_lvlup[lvl - 1][i])
			good = -1;
	if (good == -1)
		tmp_to_bc(&e->users[cs]->buf_write, "ko", 1);
	else
	{
		lvl = e->users[cs]->player.lvl++;
		tmp_to_bc(&e->users[cs]->buf_write, "", 0);
		char_to_bc(&e->users[cs]->buf_write, '0' + lvl);
		char_to_bc(&e->users[cs]->buf_write, '\n');
	}
}
