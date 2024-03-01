/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:31:40 by kchan             #+#    #+#             */
/*   Updated: 2024/03/01 22:56:19 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_check_start_time(t_philo *philo)
{
	t_rules	*rules;

	rules = *(philo->rules);
	if (gettime_ms() - rules->time_sim_start > rules->time_rule_die)
	{
		philo->is_alive = 0;
		philo->time_death = gettime_ms();
		print_death_log(philo, "died", RED);
		return (1);
	}
	return (0);
}

int	death_check(t_philo *philo)
{
	t_rules	*rules;

	rules = *(philo->rules);
	pthread_mutex_lock(rules->death_check_mutex);
	if (philo->fork_acquired < 2 && philo->meal_count == 0)
		if (death_check_start_time(philo))
			return (1);
	if (philo->meal_count > 0)
	{
		if (gettime_ms() - philo->time_last_meal > rules->time_rule_die)
		{
			philo->is_alive = 0;
			philo->time_death = gettime_ms();
			print_death_log(philo, "died", RED);
			return (1);
		}
	}
	pthread_mutex_unlock(rules->death_check_mutex);
	return (0);
}

void	eating(t_philo *philo)
{
	t_rules	*rules;

	rules = *(philo->rules);
	if (rules->philo_die != 1 && rules->meal_stop != 1)
	{
		print_log(philo, "is eating", YELLOW);
		philo->time_last_meal = gettime_ms();
		sleep_with_timeout(rules->time_rule_eat);
		philo->meal_count++;
		rules->total_meal_count++;
	}
}

void	sleeping(t_philo *philo)
{
	t_rules	*rules;

	rules = *(philo->rules);
	if (rules->philo_die != 1 && rules->meal_stop != 1)
	{
		print_log(philo, "is sleeping", GREEN);
		sleep_with_timeout(rules->time_rule_sleep);
	}
}

void	thinking(t_philo *philo)
{
	t_rules	*rules;

	rules = *(philo->rules);
	if (rules->philo_die != 1 && rules->meal_stop != 1)
		print_log(philo, "is thinking", BLUE);
}
