/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 20:25:53 by kawai             #+#    #+#             */
/*   Updated: 2024/02/16 20:58:30 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void create_philo_thread(t_rules **rules)
{
	int i;

	i = 0;
	while (i < (*rules)->philo_number)
	{
		// (*rules)->philo[i].time_last_meal = gettime_ms();
		if (pthread_create(&(*rules)->philo[i].thread_id, 
			NULL, routine, &(*rules)->philo[i]) != 0)
			error_exit("failed to create thread for a philo", rules);
		i++;
	}
}

void	eating(t_philo *philo)
{
	printf("philo %d is eating.\n", philo->philo_id);
}

void	sleeping(t_philo *philo)
{
	printf("philo %d is sleeping.\n", philo->philo_id);
}

void *routine(void *philo_ptr) 
{
	t_philo *philo;
	t_rules *rules;
	
	philo = (t_philo *)philo_ptr;
	rules = *(philo->rules);
	philo->time_creation = gettime_ms();
	philo->time_last_meal = philo->time_creation;
	while (1) 
	{
		if (philo->philo_id % 2 != 0)
		{
			if(rules->fork_state[1]==0)
			eating(philo);
		}
		else
		{
			sleeping(philo);
			printf("Philosopher %d is thinking\n", philo->philo_id);
		}
		sleep(1);
	}
	return NULL;
}

void	philo_pthread_join(t_rules **rules)
{
	int i = 0;
	while (i < (*rules)->philo_number)
	{
		pthread_join((*rules)->philo[i].thread_id, NULL);
		i++;
	}
}

void	engine(t_rules **rules)
{
	create_philo_thread(rules);
	philo_pthread_join(rules);
}
