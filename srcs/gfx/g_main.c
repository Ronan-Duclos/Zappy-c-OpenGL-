/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/17 15:28:15 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/24 20:00:50 by tmielcza         ###   ########.fr       */
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
	char	*av2[3];

	av2[0] = ft_strdup(av[0]);
	av2[1] = ft_strdup(av[1]);
	av2[2] = ft_strdup(av[2]);
	srand(time(NULL));
	ipv_init(&ipv, ac, av);
	init_glut(ac, av);
	env_init(&ipv.env);
	resources_load(&ipv.env);
	gl_init();
	light_init();
	srv_connect(&ipv, av2);
	thread_ipv(&ipv);
	printf("starting drawing\n");
	glutMainLoop();
	pthread_exit(ipv.th);
	return (0);
}
