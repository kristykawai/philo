/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:09:35 by kawai             #+#    #+#             */
/*   Updated: 2024/02/29 18:27:41 by kchan            ###   ########.fr       */
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

int	check_eat_min(t_philo *philo)
{
	int i;
	t_rules *rules;

	rules = *(philo->rules);
	i = 0;
	while(i < rules->philo_number)
		{
			if (rules->philo[i].meal_count == rules->min_meal_count
				&& rules->total_meal_count == rules->philo_number * 
				rules->min_meal_count)
				return(1);
			i++;
		}
		return (0);
}

void	*monitor_routine(void *philo_ptr)
{
	t_rules *rules;
	t_philo *philo;

	philo = (t_philo*)philo_ptr;
	rules = *(philo->rules);
	while (philo->is_alive == 1 && rules->philo_die != 1) 
	{
		pthread_mutex_lock(rules->access_mutex);
		// if (rules->philo_number == 1)
		// {
		// 	if (gettime_ms() > rules->time_rule_die)
		// 	{
		// 		philo->is_alive = 0;
		// 		philo->time_death = gettime_ms();
		// 		rules->philo_die = 1;
		// 		if(rules->philo_die == 1)
		// 			print_death_log(philo, "is dead.");
		// 		rules->time_death = philo->time_death;
		// 	}
		// }
		if (gettime_ms() - philo->time_last_meal > rules->time_rule_die)
		{
			philo->is_alive = 0;
			philo->time_death = gettime_ms();
			rules->philo_die = 1;
			if(rules->philo_die == 1)
				print_death_log(philo, "is dead.");
			rules->time_death = philo->time_death;
		}
		if(find_death(philo))
			rules->philo_die = 1;
				// rules->time_death = philo->time_death;
		else if (check_eat_min(philo) == 1)
			rules->meal_stop = 1;
		pthread_mutex_unlock(rules->access_mutex);
	}
	pthread_mutex_lock(rules->death_check_mutex);
    rules->death_check_done++;
    pthread_mutex_unlock(rules->death_check_mutex);
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
