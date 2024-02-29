/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:01:56 by kchan             #+#    #+#             */
/*   Updated: 2024/02/29 19:44:20 by kchan            ###   ########.fr       */
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
	return(current_time_ms);
}

long process_time_ms(long start_time, long end_time)
{
	return(end_time - start_time);
}

void	init_sim_time(t_rules ** rules)
{
	time_t creation_time;

	creation_time = gettime_ms(); 
	if(creation_time == -1)
		error_exit("creation time failed.\n", rules);
	(*rules)->time_sim_start = creation_time;
}

// int	sleep_with_timeout(long duration_us, t_philo *philo, int (*condition)(t_philo *))
// {
// 	struct	timeval start_time;
// 	struct	timeval end_time;
// 	long	remaining_time_us;
// 	long	elapsed_time_us;
	
// 	gettimeofday(&start_time, NULL);
// 	remaining_time_us = duration_us;
//     while (remaining_time_us > 0)
// 	{
// 		if (condition(philo) == 1)
// 			return (1);
// 		usleep(remaining_time_us);
// 		gettimeofday(&end_time, NULL);
// 		elapsed_time_us = (end_time.tv_sec - start_time.tv_sec) * 1000000 +
// 							(end_time.tv_usec - start_time.tv_usec);

// 		remaining_time_us = duration_us - elapsed_time_us;
// 		if (remaining_time_us <= 0)
// 			return (0);
// 	}
// 	return (0);
// }

void	sleep_with_timeout(long duration_milliseconds)
{
	long start;

	start = gettime_ms();
	while(gettime_ms() - start < duration_milliseconds)
		usleep(duration_milliseconds/10);//micro sec
}
