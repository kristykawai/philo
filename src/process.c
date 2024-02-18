/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:31:40 by kchan             #+#    #+#             */
/*   Updated: 2024/02/18 18:59:52 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int find_available_fork(int *fork_state, int philo_nb)
{
	int i;

	i = 0;
	while(i < philo_nb)
	{
		if (fork_state[i] == 0)
			return (i);
		i++;
	}
	return (-1);
}

int check_assign_fork(t_philo *philo)
{
	t_rules *rules;
	int fork_index;

	fork_index = -1;
	rules = *(philo->rules);
	fork_index = find_available_fork(rules->fork_state, rules->philo_number);
	if(fork_index != -1)
	{
		pthread_mutex_lock(&rules->fork[fork_index]);
		rules->fork_state[fork_index] = 1;
		print_log(philo, "has taken a fork.");
	}	
	return(fork_index);
}

void try_to_acquire_forks(t_philo *philo)
{
	t_rules *rules;

	rules = *(philo->rules);
	pthread_mutex_lock(rules->fork_array_mutex);
	if (philo->left_fork_id == -1)
		philo->left_fork_id = check_assign_fork(philo); //new fork if possible
	if (philo->right_fork_id == -1)
		philo->right_fork_id = check_assign_fork(philo); //new fork if possible
	pthread_mutex_unlock(rules->fork_array_mutex);
}

void	put_down_forks(t_philo *philo) 
{
	t_rules *rules;
	
	rules = *(philo->rules);
	pthread_mutex_lock(rules->fork_array_mutex);
	if (philo->left_fork_id != -1)
	{
		pthread_mutex_unlock(&rules->fork[philo->left_fork_id]);
		rules->fork_state[philo->left_fork_id] = 0;
		print_log(philo, "has put down a fork.");
		philo->left_fork_id = -1;
	}
	if (philo->right_fork_id != -1)
	{
		pthread_mutex_unlock(&rules->fork[philo->right_fork_id]);
		rules->fork_state[philo->right_fork_id] = 0;
		print_log(philo, "has put down a fork.");
		philo->right_fork_id = -1;
	}
	pthread_mutex_unlock(rules->fork_array_mutex);
}

void	eating(t_philo *philo)
{
	t_rules *rules;

	rules = *(philo->rules);
	philo->time_last_meal = gettime_ms();
	print_log(philo,"is eating.");
	printf("philo number:%d\n",philo->philo_id);
	usleep(rules->time_rule_eat * 1000);
	// printf("last meal time updated: %ld\n", philo->time_last_meal);
	philo->meal_count++;
	// printf("philo %d meal count: %d\n", philo->philo_id,philo->meal_count);
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
	t_rules *rules;

	rules = *(philo->rules);
	eating(philo);
	put_down_forks(philo);
	sleeping(philo);
	if (philo->philo_id % 2 != 0)
	rules->odd_turn_count++;
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
        pthread_mutex_unlock(rules->turn_mutex);  // Unlock before attempting to pick up forks

        if ((philo->philo_id % 2 != 0 && rules->odd_turn_count < rules->total_odd_philo) ||
            (philo->philo_id % 2 == 0 && rules->odd_turn_count == rules->total_odd_philo))
        {
            pthread_mutex_lock(rules->access_mutex);  // Lock critical section
            try_to_acquire_forks(philo);
            eat_and_sleep_think(philo);
            put_down_forks(philo);
            pthread_mutex_unlock(rules->access_mutex);  // Unlock critical section
        }
        else 
        {            	
            pthread_mutex_unlock(rules->turn_mutex);  // Unlock when it's not the philosopher's turn
            sleeping(philo);
            print_log(philo, "is sleeping.\n");
        }

        pthread_mutex_lock(rules->turn_mutex);  // Lock to update turn
        rules->current_turn++;
        pthread_mutex_unlock(rules->turn_mutex);  // Unlock after updating turn
        usleep(1000);
    }
}
