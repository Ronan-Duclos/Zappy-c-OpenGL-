
#include <client.h>
#include <common.h>

void	send_move_forward(t_env *e)
{
	int			a_write;
	t_actions	*acts;

	a_write = e->user->player.cur_awrite;
	acts = e->user->player.acts;
	acts->time = 1;
	/*acts->fct_cmd = move_forward;*/
	tmp_to_bc(&e->user->buf_write, "avance", 1);
	e->user->player.cur_awrite = (e->user->player.cur_awrite + 1) % 10;
}
