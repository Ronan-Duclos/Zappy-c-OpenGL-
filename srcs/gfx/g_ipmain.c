/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_ipmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 11:25:03 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/16 19:37:55 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include "gfx.h"

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
	ipv_loop(&ipv);
	printf("starting drawing\n");
	glutMainLoop();
	return (0);
}
