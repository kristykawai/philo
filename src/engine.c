/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 20:25:53 by kawai             #+#    #+#             */
/*   Updated: 2024/02/16 20:37:49 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void create_philo_thread(t_rules **rules)
{
	int i;

	i = 0;
	while (i < (*rules)->philo_number)
	{
		printf("current i:%d\n",i);
	if (pthread_create(&(*rules)->philo[i].thread_id, 
		NULL, test, &(*rules)->philo[i]) != 0)
			error_exit("failed to create thread for a philo", rules);
		i++;
	}
}

void *test(void *philo_ptr) 
{
    t_philo *philo;
	t_rules *rules;
	
	philo = (t_philo *)philo_ptr;
	rules = *(philo->rules);
	while (1) 
	{
		printf("Philosopher %d is thinking\n", philo->philo_id);
		printf("address %p\n", rules->philo);
		sleep(1);
	}
	return NULL;
}

void	philo_pthread_join(t_rules **rules)
{
	int i = 0;
	while (i < (*rules)->philo_number)
	{
		pthread_join((*rules)->philo[i].thread_id, NULL);
		i++;
	}
}

void	engine(t_rules **rules)
{
	create_philo_thread(rules);
	philo_pthread_join(rules);
}
