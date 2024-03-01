/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:16:33 by kawai             #+#    #+#             */
/*   Updated: 2024/03/01 23:03:58 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_and_sleep_think(t_philo *philo)
{
	eating(philo);
	put_down_forks(philo);
	sleeping(philo);
	thinking(philo);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)philo_ptr;
	rules = *(philo->rules);
	philo->time_creation = gettime_ms();
	while (rules->meal_stop != 1 && rules->philo_die != 1)
	{
		if (philo->meal_count <= rules->total_meal_count / rules->philo_number)
		{
			while (!philo->fork_acquired)
				try_to_acquire_forks(philo);
			if (philo->left_fork_id != -1 && philo->right_fork_id != -1
				&& philo->is_alive == 1 && rules->meal_stop != 1)
			{
				if (death_check(philo) != 1)
				{
					eat_and_sleep_think(philo);
					put_down_forks(philo);
				}
			}
		}
	}
	return (NULL);
}
