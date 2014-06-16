/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/16 21:14:10 by rduclos           #+#    #+#             */
/*   Updated: 2014/06/16 21:14:11 by rduclos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <time.h>
#include <stdio.h>

double		ft_usec_time(void)
{
	struct timeval	tv;
	struct timezone	tz;
	struct tm		*tm;
	double			my_time;

	gettimeofday(&tv, &tz);
	tm = localtime(&tv.tv_sec);
	my_time = 0;
	my_time = (my_time + tm->tm_hour) * 60;
	my_time = (my_time + tm->tm_min) * 60;
	my_time = ((my_time + tm->tm_sec) * 1000000) + tv.tv_usec;
	return (my_time);
}
