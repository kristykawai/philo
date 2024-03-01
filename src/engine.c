/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 20:25:53 by kawai             #+#    #+#             */
/*   Updated: 2024/03/01 23:37:06 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philo_thread(t_rules **rules)
{
	int	i;

	i = 0;
	while (i < (*rules)->philo_number)
	{
		if (pthread_create(&(*rules)->philo[i].thread_id,
				NULL, routine, &(*rules)->philo[i]) != 0)
			error_exit("failed to create thread for a philo", rules);
		i++;
	}
}

void	philo_pthread_join(t_rules **rules)
{
	int	i;

	i = 0;
	while (i < (*rules)->philo_number)
	{
		pthread_join((*rules)->philo[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < (*rules)->philo_number)
	{
		pthread_join((*rules)->philo[i].thread_monitor_id, NULL);
		i++;
	}
}

void	engine(t_rules **rules)
{
	create_philo_thread(rules);
	create_monitor_thread(rules);
	philo_pthread_join(rules);
}
