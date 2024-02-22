/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 20:25:53 by kawai             #+#    #+#             */
/*   Updated: 2024/02/23 00:00:32 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void create_philo_thread(t_rules **rules)
{
	int i;

	i = 0;
	while (i < (*rules)->philo_number)
	{
		if (pthread_create(&(*rules)->philo[i].thread_id, 
			NULL, routine, &(*rules)->philo[i]) != 0)
			error_exit("failed to create thread for a philo", rules);
		i++;
	}
}

void	philo_pthread_join(t_rules **rules)
{
	int i = 0;
	while (i < (*rules)->philo_number && (*rules)->philo_die != 1)
	{
		pthread_join((*rules)->philo[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < (*rules)->philo_number && (*rules)->philo_die != 1)
	{
		pthread_join((*rules)->philo[i].thread_monitor_id, NULL);
		i++;
	}
}

void	engine(t_rules **rules)
{
	// t_philo *philo_ptr;
	create_philo_thread(rules);
	create_monitor_thread(rules);
	while (1) 
	{
		pthread_mutex_lock((*rules)->access_mutex);
		if ((*rules)->philo_die)
		{
			// printf("death gap time:%ld\n", (long)gettime_ms() - (*rules)->time_death);
			error_exit("one philo died. simulation stop\n", rules);
		}
		pthread_mutex_unlock((*rules)->access_mutex);
	}
	philo_pthread_join(rules);
}
