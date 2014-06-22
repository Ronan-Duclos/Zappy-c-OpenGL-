#include <client.h>
#include <common.h>

void	receive_ok_only(t_env *e)
{
	int			ar;
	t_actions	*act;

	ar = e->user->player.cur_aread;
	act = &e->user->player.acts[ar];
	act->time = 0;
}
