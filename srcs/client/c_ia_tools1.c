
#include <client.h>
#include <common.h>

void	make_trvl(t_env *e, int x, int y)
{
	int		my_x;
	int		my_y;
	int		dest_x;
	int		dest_y;
	int		i;

	my_x = e->user->player.ia.x;
	my_y = e->user->player.ia.y;
	dest_x = x - my_x;
	dest_y = y - my_y;
	if (dest_x < 0)
		dest_x = dest_x * (-1);
	if (dest_y < 0)
		dest_y = dest_y * (-1);
	i = dest_x + dest_y + 2;
	e->users->player.ia.trvl = (int *)XV(NULL, malloc(sizeof(int) * i), "malloc");
	i = 0;
	while ()
}
