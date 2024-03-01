/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:01:56 by kchan             #+#    #+#             */
/*   Updated: 2024/03/01 19:51:06 by kchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timestamp_ms(t_rules **rules)
{
	return (gettime_ms() - (*rules)->time_sim_start);
}

long	gettime_ms(void)
{
	struct timeval		current_time;
	time_t				current_time_ms;

	if (gettimeofday(&current_time, NULL) != 0)
		return (-1);
	current_time_ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (current_time_ms);
}

void	init_sim_time(t_rules **rules)
{
	time_t	creation_time;

	creation_time = gettime_ms();
	if (creation_time == -1)
		error_exit("creation time failed.\n", rules);
	(*rules)->time_sim_start = creation_time;
}

void	sleep_with_timeout(long duration_milliseconds)
{
	long	start;

	start = gettime_ms();
	while (gettime_ms() - start < duration_milliseconds)
		usleep(duration_milliseconds / 10);
}

int	longest_wait_philo(t_philo *philo)
{
	t_rules	*rules;
	int		i;

	i = 0;
	rules = *(philo->rules);
	while (i < rules->philo_number)
	{
		if (philo->time_last_meal > rules->philo[i].time_last_meal)
			return (0);
		i++;
	}
	return (1);
}
