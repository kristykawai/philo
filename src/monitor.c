/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:09:35 by kawai             #+#    #+#             */
/*   Updated: 2024/03/01 20:28:40 by kchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_condition_lancher(t_rules **rules)
{
	pthread_mutex_lock((*rules)->access_mutex);
	print_exit_condition_lancher_log(rules);
	pthread_mutex_unlock((*rules)->access_mutex);
}

void	print_exit_condition_lancher_log(t_rules **rules)
{
	if ((*rules)->meal_stop)
	{
		print_death_log(latest_eat_philo((*rules)->philo),
			"finished meal. Meal stop condition reached.\n", RED);
		cleanup_rules(rules);
		exit(0);
	}
	if ((*rules)->philo_die)
	{
		error_exit("philo die\n", rules);
	}
}

void	*find_death(t_philo *philo)
{
	int		i;
	t_rules	*rules;

	rules = *(philo->rules);
	i = 0;
	while (i < rules->philo_number)
	{
		if (rules->philo[i].is_alive == 0)
			return (&rules->philo[i]);
		i++;
	}
	return (0);
}

int	check_eat_min(t_philo *philo)
{
	int		i;
	t_rules	*rules;

	rules = *(philo->rules);
	i = 0;
	while (i < rules->philo_number)
	{
		if (rules->philo[i].meal_count == rules->min_meal_count
			&& rules->total_meal_count == rules->philo_number
			* rules->min_meal_count)
			return (1);
		i++;
	}
	return (0);
}

void	*monitor_routine(void *philo_ptr)
{
	t_rules		*rules;
	t_philo		*philo;

	philo = (t_philo *)philo_ptr;
	rules = *(philo->rules);
	while (1)
	{
		if (check_eat_min(philo) == 1)
		{
			rules->meal_stop = 1;
			exit_condition_lancher(&rules);
		}
		if (death_check(philo) == 1)
		{
			rules->philo_die = 1;
			exit_condition_lancher(&rules);
		}
	}
	return (NULL);
}

void	create_monitor_thread(t_rules **rules)
{
	int	i;

	i = 0;
	while (i < (*rules)->philo_number)
	{
		if (pthread_create(&(*rules)->philo[i].thread_monitor_id,
				NULL, monitor_routine, &(*rules)->philo[i]) != 0)
			error_exit("failed to create thread for a philo", rules);
		i++;
	}
}
