/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:09:35 by kawai             #+#    #+#             */
/*   Updated: 2024/02/22 18:24:45 by kchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void handle_philosopher_death(t_philo *philo) 
{
	t_rules *rules;

	rules = *(philo->rules);
	print_log(philo, "is dead.");
	// error_exit("Philosopher died.", &rules);
	// (NULL);
}

void	*monitor_routine(void *philo_ptr)
{
	t_rules *rules;
	t_philo *philo;

	philo = (t_philo*)philo_ptr;
	rules = *(philo->rules);
	while (philo->is_alive == 1) 
	{
		if (gettime_ms() - philo->time_last_meal >= rules->time_rule_die)
		{
			philo->is_alive = 0;
			handle_philosopher_death(philo);
		}
		usleep(10000);
	}
	return (NULL);
}

void create_monitor_thread(t_rules **rules)
{
int i;

	i = 0;
	while (i < (*rules)->philo_number)
	{
		if (pthread_create(&(*rules)->philo[i].thread_monitor_id, 
			NULL, monitor_routine, &(*rules)->philo[i]) != 0)
			error_exit("failed to create thread for a philo", rules);
		i++;
	}
}

	// t_rules **rules;
	// rules = (t_rules **)rule_ptr;
	// int i;

	// i = -1;
	// while(1)
	// {
	// 	while (++i < (*rules)->philo_number)
	// 	{
	// 		if ((*rules)->philo[i].is_alive) 
	// 		{
	// 			if (gettime_ms() - (*rules)->philo[i].time_last_meal >= (*rules)->time_rule_die) //last_meal time not updated
	// 			{
	// 				(*rules)->philo[i].is_alive = 0;
	// 				error_exit("process time smaller than time to die", rules); // tbc to check how to kill the thread 
	// 			}
	// 			else
	// 				(*rules)->philo[i].is_alive = 1;
	// 		}
	// 	}
	// usleep(10000);
	// }
	// return NULL;