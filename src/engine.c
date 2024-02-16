/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 20:25:53 by kawai             #+#    #+#             */
/*   Updated: 2024/02/16 23:17:12 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	eating(t_philo *philo)
{
	print_log(*(philo->rules),"is eating.");
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
			usleep(1000);
			printf("processed time:%ld\n", (long)process_time_ms(philo->time_creation, gettime_ms()));
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
	// create_monitor_thread(rules);
	philo_pthread_join(rules);
}
