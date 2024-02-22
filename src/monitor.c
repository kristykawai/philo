/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:09:35 by kawai             #+#    #+#             */
/*   Updated: 2024/02/22 23:32:11 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *find_death(t_philo *philo)
{
	int i;
	t_rules *rules;

	rules = *(philo->rules);
	i = 0;
	while(i < rules->philo_number)
		{
			if (rules->philo[i].is_alive == 0)
				return(&rules->philo[i]);
			i++;
		}
	return (0);
}

// void handle_philosopher_death(t_philo *philo) 
// {
// 	// t_rules *rules;

// 	// rules = *(philo->rules);
// 	print_log(philo, "is dead.");
// 	// error_exit("Philosopher died.", &rules);
// 	// (NULL);
// }

void	*monitor_routine(void *philo_ptr)
{
	t_rules *rules;
	t_philo *philo;

	philo = (t_philo*)philo_ptr;
	rules = *(philo->rules);
	while (philo->is_alive == 1 && rules->philo_die != 1) 
	{
		pthread_mutex_lock(rules->access_mutex);
		if (gettime_ms() - philo->time_last_meal >= rules->time_rule_die)
		{
			philo->is_alive = 0;
			philo->time_death = gettime_ms();
			if(rules->philo_die == 0)
				print_log(philo, "is dead.");
			rules->time_death = philo->time_death;
			rules->philo_die = 1;
		}
		pthread_mutex_unlock(rules->access_mutex);
		usleep(1000);
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