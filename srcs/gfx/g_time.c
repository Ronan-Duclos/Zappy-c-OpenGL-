/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_time.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 20:15:00 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/13 20:32:09 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "gfx_gl.h"

int		time_frame(void)
{
	static double	oldtime = 0;
	static double	spf = 1.0 / FPS;
	double			time;

	if (oldtime == 0)
		oldtime = (double)clock() / CLOCKS_PER_SEC;
	time = (double)clock() / CLOCKS_PER_SEC;
	if (time - oldtime >= spf)
	{
		oldtime += spf;
		return (0);
	}
	return (1);
}
