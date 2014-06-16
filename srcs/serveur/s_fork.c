
#include <serveur.h>
#include <common.h>
#include <libft.h>

void	my_fork(t_env *e, int cs)
{
	int		i;

	i = -1;
	while (e->opt.name[++i] != NULL)
		if (ft_strcmp(e->users[cs]->player.team, e->team[i].name) == 0)
		{
			if (e->team[i].member < ((e->srv.max_fd - 4) / 2))
				tmp_to_bc(&e->users[cs]->buf_write, "ok", 1);
			else
				tmp_to_bc(&e->users[cs]->buf_write, "ko", 1);
		}

}
