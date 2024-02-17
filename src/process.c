/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:31:40 by kchan             #+#    #+#             */
/*   Updated: 2024/02/17 19:35:23 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void try_to_acquire_forks(t_philo *philo) 
{
	t_rules *rules;
	
	rules = *(philo->rules);
	pthread_mutex_lock(&rules->fork[philo->left_fork_id]);
	rules->fork_state[philo->left_fork_id] = 1;
	print_log(philo, "has taken a left fork.");
    pthread_mutex_lock(&rules->fork[philo->right_fork_id]);
	rules->fork_state[philo->right_fork_id] = 1;
	print_log(philo, "has taken a right fork.");
}

void	eating(t_philo *philo)
{
	print_log(philo,"is eating.");
	printf("philo number:%d\n",philo->philo_id);
	philo->time_last_meal = gettime_ms();
	printf("last meal time updated: %ld\n", philo->time_last_meal);
	philo->meal_count++;
}

void put_down_forks(t_philo *philo) 
{
	t_rules *rules;

	rules = *(philo->rules);
	rules->fork_state[philo->left_fork_id] = 0;
	print_log(philo, "has put down a left fork.");
	pthread_mutex_unlock(&rules->fork[philo->left_fork_id]);
	rules->fork_state[philo->right_fork_id] = 0;
	print_log(philo, "has put down a right fork.");
	pthread_mutex_unlock(&rules->fork[philo->right_fork_id]);
}

void	sleeping(t_philo *philo)
{
	print_log(philo, "is sleeping.");
}

void eat_and_sleep(t_philo *philo)
{
	t_rules *rules;

	rules = *(philo->rules);
	eating(philo);
	put_down_forks(philo);
	if (philo->philo_id % 2 != 0)
	rules->odd_turn_count++;
	usleep(rules->time_rule_eat * 1000);
	printf("processed time:%ld\n", (long)process_time_ms(philo->time_creation, gettime_ms()));
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
	    pthread_mutex_unlock(rules->turn_mutex);  // Unlock before attempting to pick up forks
		if ((philo->philo_id % 2 != 0 && rules->odd_turn_count < rules->total_odd_philo) ||
			(philo->philo_id % 2 == 0 && rules->odd_turn_count == rules->total_odd_philo))
		{
            pthread_mutex_lock(rules->access_mutex);  // Lock critical section
            if (rules->fork_state[philo->left_fork_id] == 0 && rules->fork_state[philo->right_fork_id] == 0)
				{
        	        try_to_acquire_forks(philo);
            	    eat_and_sleep(philo);
            	}
        	pthread_mutex_unlock(rules->access_mutex);  // Unlock critical section
        }
		else 
		{            	
			pthread_mutex_unlock(rules->turn_mutex);  // Unlock when it's not the philosopher's turn
        	sleeping(philo);
			print_log(philo, "is thinking.\n");
        }
        pthread_mutex_lock(rules->turn_mutex);  // Lock to update turn
		rules->current_turn++;
        pthread_mutex_unlock(rules->turn_mutex);  // Unlock after updating turn
        sleep(1);
	}
}

// void odd_philosopher_rountine(void *philo_ptr)
// {
// 	t_philo *philo;
// 	t_rules *rules;
	
// 	philo = (t_philo *)philo_ptr;
// 	rules = *(philo->rules);
// 	if(rules->fork_state[philo->left_fork_id] == 0 && rules->fork_state[philo->right_fork_id] == 0)
// 	{
// 		pthread_mutex_lock(&rules->fork[philo->left_fork_id]);
// 		rules->fork_state[philo->left_fork_id] = 1;
// 		print_log(philo,"has taken a left fork.");
// 		pthread_mutex_lock(&rules->fork[philo->right_fork_id]);		
// 		rules->fork_state[philo->right_fork_id] = 1;
// 		print_log(philo,"has taken a right fork.");
// 		eating(philo);
// 		rules->fork_state[philo->left_fork_id] = 0;
// 		print_log(philo,"has put down a left fork.");
// 		pthread_mutex_unlock(&rules->fork[philo->left_fork_id]);
// 		rules->fork_state[philo->right_fork_id] = 0;
// 		print_log(philo,"has put down a right fork.");
// 		pthread_mutex_unlock(&rules->fork[philo->right_fork_id]);
// 	}
// 	else
// 	{
// 		sleeping(philo);
// 		printf("Philosopher %d is thinking\n", philo->philo_id);
// 	}
// 	usleep(1000);
// 	printf("processed time:%ld\n", (long)process_time_ms(philo->time_creation, gettime_ms()));
// }
