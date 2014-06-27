/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/17 15:28:15 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/27 10:27:15 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include "gfx.h"

void		thread_ipv(t_ipv *ipv)
{
	pthread_create(&ipv->th, NULL, ipv_loop, ipv);
}

int			main(int ac, char **av)
{
	t_ipv	ipv;

	srand(time(NULL));
	ipv_init(&ipv, ac, av);
	init_glut(ac, av);
	env_init(&ipv.env);
	resources_load(&ipv.env);
	gl_init();
	light_init();
	srv_connect(&ipv, av);
	thread_ipv(&ipv);
	glutMainLoop();
	pthread_exit(ipv.th);
	return (0);
}
