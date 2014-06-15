/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_ipmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caupetit <caupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 11:25:03 by caupetit          #+#    #+#             */
/*   Updated: 2014/06/15 12:18:39 by caupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gfx.h"

int			main(int ac, char **av)
{
	t_ipv	ipv;
	t_env	env;

	srand(time(NULL));
	init_glut(ac, av);
	env_init(&env);
	resources_load(&env);
	gl_init();
	ipv_init(&ipv, ac, av);
	light_init();
	srv_connect(&ipv, av);
	ipv_loop(&ipv);
	printf("starting drawing\n");
	glutMainLoop();
	return (0);
}
