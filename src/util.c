/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:38:10 by kchan             #+#    #+#             */
/*   Updated: 2024/02/23 11:40:43 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_log(t_philo *philo, char *msg)
{	
	t_rules *rules;
	
	rules = *(philo->rules);
	pthread_mutex_lock(rules->writing_mutex);
	if(!rules->philo_die && rules->meal_stop != 1)
		printf("%ld philosopher %d %s\n", gettime_ms(), philo->philo_id, msg);
	pthread_mutex_unlock(rules->writing_mutex);
	return	;
}

void print_death_log(t_philo *philo, char *msg)
{	
	t_rules *rules;
	
	rules = *(philo->rules);
	pthread_mutex_lock(rules->writing_mutex);
		printf("%ld philosopher %d %s\n", gettime_ms(), philo->philo_id, msg);
	pthread_mutex_unlock(rules->writing_mutex);
	return	;
}
