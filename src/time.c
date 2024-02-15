/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:01:56 by kchan             #+#    #+#             */
/*   Updated: 2024/02/15 17:10:27 by kchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime_ms(void)
{
	struct  timeval current_time;
	time_t current_time_ms;

	if(gettimeofday(&current_time, NULL) != 0)
		return(-1);
	current_time_ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	// printf("millisecond: %ld\n",(long)current_time.tv_usec);
	return(current_time_ms);
}

void	init_sim_time(t_rules ** rules)
{
	time_t creation_time;

	creation_time = gettime_ms(); 
	if(creation_time == -1)
		error_exit("creation time failed.\n", rules);
	(*rules)->time_sim_start = creation_time;
}
