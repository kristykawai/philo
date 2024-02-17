/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:09:35 by kawai             #+#    #+#             */
/*   Updated: 2024/02/17 18:50:28 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_thread(void *rule_ptr)
{
	t_rules **rules;
	rules = (t_rules **)rule_ptr;
	int i;

	i = -1;
	while(1)
	{
		while (++i < (*rules)->philo_number)
		{
			if ((*rules)->philo[i].is_alive) 
			{
				if (gettime_ms() - (*rules)->philo[i].time_last_meal >= (*rules)->time_rule_die) //last_meal time not updated
				{
					(*rules)->philo[i].is_alive = 0;
					error_exit("process time smaller than time to die", rules); // tbc to check how to kill the thread 
				}
				else
					(*rules)->philo[i].is_alive = 1;
			}
		}
	usleep(10000);
	}
	return NULL;
}

void create_monitor_thread(t_rules **rules)
{
	pthread_t monitor_thread_id;
	pthread_create(&monitor_thread_id, NULL, monitor_thread, rules);
}
