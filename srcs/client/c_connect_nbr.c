
#include <client.h>
#include <common.h>

void	send_connect_nbr(t_env *e)
{
	int			a_write;
	t_actions	*acts;

	a_write = e->user->player.cur_awrite;
	acts = e->user->player.acts;
	acts->time = 1;
	/*acts->fct_cmd = connect_nbr;*/
	tmp_to_bc(&e->user->buf_write, "connect_nbr", 1);
	e->user->player.cur_awrite = (e->user->player.cur_awrite + 1) % 10;
}
