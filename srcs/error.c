/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 13:54:10 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/11 13:56:45 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int		x_int(int err, int res, char *str, char *file)
{
	if (res == err)
	{
		fprintf(stderr, "%s error (%s): Line (%d) :%s\n", 
				str, file, __LINE__, strerror(errno));
		exit (1);
	}
	return (res);
}

void	*x_void(void *err, void *res, char *str, char *file)
{
	if (res == err)
	{
		fprintf(stderr, "%s error (%s): Line (%d) :%s\n", 
				str, file, __LINE__, strerror(errno));
		exit (1);
	}
	return (res);
}
