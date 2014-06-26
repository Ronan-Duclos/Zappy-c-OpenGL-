/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_serveur_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/17 21:24:20 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/26 11:59:39 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>
#include <common.h>

int		check_word(char *str, char *str2)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && str2[i] != '\0')
	{
		if (str[i] != str2[i])
			return (-1);
		i++;
	}
	return (0);
}
/*
void	rcv_keyboard(t_env *e)
{
	char	*line;

	line = NULL;
	get_next_line(0, &line);
	if (line == NULL)
		return ;
	if (check_word(line, "prend") == 0)
		send_take_item(e, line + 6);
	else if (check_word(line, "pose") == 0)
		send_drop_item(e, line + 5);
	else if (check_word(line, "avance") == 0)
		send_move_forward(e);
	else if (check_word(line, "voir") == 0)
		send_watch_sight(e);
	else if (check_word(line, "inventaire") == 0)
		send_inventaire(e);
	else if (check_word(line, "droite") == 0)
		send_turn_right(e);
	else if (check_word(line, "gauche") == 0)
		send_turn_left(e);
	else if (check_word(line, "expulse") == 0)
		send_expulse(e);
	else if (check_word(line, "broadcast") == 0)
		send_broadcast(e, line + 9);
	else if (check_word(line, "incantation") == 0)
		send_incantation(e);
	else if (check_word(line, "fork") == 0)
		send_fork(e);
	else if (check_word(line, "connect_nbr") == 0)
		send_connect_nbr(e);
	free(line);
}
*/
void	send_serveur(t_env *e)
{
	int		i;

	bc_to_tmp(&e->user->buf_write, e->user->buf_write_tmp);
	i = ft_strlen(e->user->buf_write_tmp);
	if (e->me.v)
		printf("\033[32mSend : \033[0m%s", e->user->buf_write_tmp);
	send(e->user->sock, e->user->buf_write_tmp, i, 0);
	ft_bzero(e->user->buf_write_tmp, i);
}
