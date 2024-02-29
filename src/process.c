/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:31:40 by kchan             #+#    #+#             */
/*   Updated: 2024/02/29 23:24:36 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int death_check(t_philo *philo)
{
	t_rules *rules;
	
	rules = *(philo->rules);
	// if(philo->meal_count > 0)
	// {
	if (gettime_ms() - philo->time_last_meal > rules->time_rule_die)		
	{
			philo->is_alive = 0;
			philo->time_death = gettime_ms();
			printf("death check success\n");
			print_death_log(philo, "is dead.", RED);
			return(1);
	}
	// } 
	// else
	// if (gettime_ms() - rules->time_sim_start > rules->time_rule_die)
	// {
	// 	philo->is_alive = 0;
	// 	philo->time_death = gettime_ms();
	// 	printf("death check success\n");
	// 	print_death_log(philo, "is dead.", RED);
	// 	return(1);
	// }
	return(0);
}

void	eating(t_philo *philo)
{
	t_rules *rules;
	
	rules = *(philo->rules);
	if(rules->philo_die != 1 && rules->meal_stop != 1)
	{
		print_log(philo,"is eating.",YELLOW);
		philo->time_last_meal = gettime_ms();
		sleep_with_timeout(rules->time_rule_eat);
		philo->meal_count++;
		rules->total_meal_count++;
	}
}

void	sleeping(t_philo *philo)
{	
	t_rules *rules;

	rules = *(philo->rules);
	if(rules->philo_die != 1 && rules->meal_stop != 1)
	{
		print_log(philo, "is sleeping.", GREEN);
		sleep_with_timeout(rules->time_rule_sleep);
	}
}

void	thinking(t_philo *philo)
{	
	t_rules *rules;

	rules = *(philo->rules);
	if(rules->philo_die != 1 && rules->meal_stop != 1)
		print_log(philo, "is thinking.",BLUE);
}

void eat_and_sleep_think(t_philo *philo)
{
	if(death_check(philo)!= 1)
		eating(philo);
	if(death_check(philo)!= 1)
		put_down_forks(philo);
	if(death_check(philo)!= 1)
		sleeping(philo);
	if(death_check(philo)!= 1)
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
				if(death_check(philo)!= 1)
					eat_and_sleep_think(philo);
				put_down_forks(philo);
			}
		}
	}
	return (NULL);
}
