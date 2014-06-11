/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 19:16:41 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/08 19:10:26 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "libft.h"

int		x_int(int err, int res, char *str, char *file)
{
	if (res == err)
	{
		fprintf(stderr, "%s error (%s): %s\n", 
				str, file, strerror(errno));
		exit (1);
	}
	return (res);
}

void	*x_void(void *err, void *res, char *str, char *file)
{
	if (res == err)
	{
		fprintf(stderr, "%s error (%s): %s\n", 
				str, file, strerror(errno));
		exit (1);
	}
	return (res);
}
