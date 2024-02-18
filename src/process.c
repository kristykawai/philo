/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:31:40 by kchan             #+#    #+#             */
/*   Updated: 2024/02/18 20:56:24 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	t_rules *rules;

	rules = *(philo->rules);
	philo->time_last_meal = gettime_ms();
	print_log(philo,"is eating.");
	usleep(rules->time_rule_eat * 1000);
	philo->meal_count++;
	rules->total_meal_count++;
}


void	sleeping(t_philo *philo)
{	
	t_rules *rules;

	rules = *(philo->rules);
	usleep(rules->time_rule_sleep * 1000);
	print_log(philo, "is sleeping.");
}

void	thinking(t_philo *philo)
{	
	print_log(philo, "is thinking.");
}

void eat_and_sleep_think(t_philo *philo)
{
	eating(philo);
	put_down_forks(philo);
	sleeping(philo);
	if (philo->philo_id % 2 != 0)
	thinking(philo);
}

void *routine(void *philo_ptr) 
{
    t_philo *philo = (t_philo *)philo_ptr;
    t_rules *rules = *(philo->rules);

    philo->time_creation = gettime_ms();
    philo->time_last_meal = philo->time_creation;
    while (1) 
    {
		if(philo->meal_count <= rules->total_meal_count/ rules->philo_number)
        {
			try_to_acquire_forks(philo);
			if(philo->left_fork_id != -1 && philo->right_fork_id != -1)
			{
				eat_and_sleep_think(philo);
				put_down_forks(philo);
			}
        }
        else 
            sleeping(philo);
        usleep(1000);
    }
}
