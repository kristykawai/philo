/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 20:50:37 by kawai             #+#    #+#             */
/*   Updated: 2024/02/23 10:55:09 by kawai            ###   ########.fr       */
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
	pthread_mutex_lock(rules->access_mutex);
	if(!find_death(philo) && !check_eat_min(philo))
	{
		if (philo->left_fork_id == -1)
			philo->left_fork_id = check_assign_fork(philo);
		if (philo->right_fork_id == -1)
			philo->right_fork_id = check_assign_fork(philo);
	}
	pthread_mutex_unlock(rules->access_mutex);
}

void	put_down_forks(t_philo *philo) 
{
	t_rules *rules;
	
	rules = *(philo->rules);
	pthread_mutex_lock(rules->access_mutex);
	if(!find_death(philo) && !check_eat_min(philo))
	{
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
	}
	pthread_mutex_unlock(rules->access_mutex);
}
