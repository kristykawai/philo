/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:31:40 by kchan             #+#    #+#             */
/*   Updated: 2024/02/29 19:20:45 by kchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int death_check(t_philo *philo)
{
	t_rules *rules;
	
	rules = *(philo->rules);
	if (gettime_ms() - philo->time_last_meal > rules->time_rule_die)
	{
		philo->is_alive = 0;
		philo->time_death = gettime_ms();
		printf("death check success\n");
		print_death_log(philo, "is dead.");
		return(1);
	} 
	return(0);
}

// int eating_condition(t_philo *philo)
// {
// 	t_rules *rules;
	
// 	rules = *(philo->rules);
//     return(gettime_ms() - philo->time_last_meal >= rules->time_rule_eat * 1000);
// }

void	eating(t_philo *philo)
{
	t_rules *rules;
	
	rules = *(philo->rules);
	if(rules->philo_die != 1 && rules->meal_stop != 1)
	{
		long start_time;
		start_time = gettime_ms();
		print_log(philo,"is eating.");
		sleep_with_timeout(rules->time_rule_eat);
		// usleep(rules->time_rule_eat * 1000);
		// print_log(philo,"finished eating.");
		if(!death_check(philo))
		{
			philo->time_last_meal = gettime_ms();
			philo->meal_count++;
			rules->total_meal_count++;
		}
		// printf("meal time:%ld\n", philo->time_last_meal - start_time);
	}
}

void	sleeping(t_philo *philo)
{	
	t_rules *rules;

	rules = *(philo->rules);
	long start_time;
	if(rules->philo_die != 1 && rules->meal_stop != 1)
	{
		start_time = gettime_ms();
		print_log(philo, "is sleeping.");
		sleep_with_timeout(rules->time_rule_sleep);
		// usleep(rules->time_rule_sleep);
		print_log(philo,"finished sleeping.");
		printf("sleep time:%ld\n", gettime_ms() - start_time);
	}
}

void	thinking(t_philo *philo)
{	
	t_rules *rules;

	rules = *(philo->rules);
	if(rules->philo_die != 1 && rules->meal_stop != 1)
		print_log(philo, "is thinking.");
}

void eat_and_sleep_think(t_philo *philo)
{
	t_rules *rules;

	rules = *(philo->rules);
	if(!find_death(philo) && rules->philo_die != 1 && rules->meal_stop != 1)
		eating(philo);
	if(!find_death(philo) && rules->philo_die != 1 && rules->meal_stop != 1)
		put_down_forks(philo);
	if(!find_death(philo) && rules->philo_die != 1 && rules->meal_stop != 1)
		sleeping(philo);
	if ((!find_death(philo)) && philo->philo_id % 2 != 0 && rules->philo_die != 1
			&& rules->meal_stop != 1)
		thinking(philo);
}

void *routine(void *philo_ptr) 
{
	t_philo *philo = (t_philo *)philo_ptr;
	t_rules *rules = *(philo->rules);

	philo->time_creation = gettime_ms();
	philo->time_last_meal = philo->time_creation;
	while (philo->is_alive == 1 && !find_death(philo) && !check_eat_min(philo)) 
	{
		if(philo->meal_count <= rules->total_meal_count/ rules->philo_number && philo->is_alive == 1
			&& rules->meal_stop != 1)
		{
			try_to_acquire_forks(philo);
			if(philo->left_fork_id != -1 && philo->right_fork_id != -1 
			&& philo->is_alive == 1 && rules->meal_stop != 1)
			{
				eat_and_sleep_think(philo);
				put_down_forks(philo);
			}
		}
		// else 
		// 	sleeping(philo);
	}
	return (NULL);
}
