
#include <client.h>
#include <common.h>

void	send_send_item(t_env *e, char *item)
{
	int			a_write;
	t_actions	*acts;
	char		buf[BUF_SIZE];

	strcpy(buf, "pose ");
	strcpy(buf + 5, item);
	a_write = e->user->player.cur_awrite;
	acts = e->user->player.acts;
	acts->time = 1;
	/*acts->fct_cmd = send_item;*/
	tmp_to_bc(&e->user->buf_write, buf, 1);
	e->user->player.cur_awrite = (e->user->player.cur_awrite + 1) % 10;
}
