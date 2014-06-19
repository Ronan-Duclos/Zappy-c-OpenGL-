
#include <client.h>
#include <common.h>

int		death_clt(t_env *e)
{
	if (ft_strcmp(e->user->buf_read_tmp, "DEAD\n") == 0)
	{
		printf("You are dead\n");
		close(e->user->sock);
		my_exit(0, "/quit");
		return (1);
	}
	return (0);
}
