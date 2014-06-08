/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 21:48:32 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/07 22:14:03 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "common.h"

void	init_clt(t_env *e)
{
	e->user = (t_user *)XV(NULL, malloc(sizeof(t_user)), "malloc");
	e->user->ig = 0;
	init_bc(&e->user->buf_read);
	init_bc(&e->user->buf_write);
}
