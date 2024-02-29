/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:38:10 by kchan             #+#    #+#             */
/*   Updated: 2024/02/29 22:07:21 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_log(t_philo *philo, char *msg, char *state_colour)
{	
	t_rules *rules;
	
	rules = *(philo->rules);
	pthread_mutex_lock(rules->writing_mutex);
	if(!rules->philo_die && rules->meal_stop != 1)
		printf("%s timestamp: %ld %ld philosopher %d %s %s\n",state_colour, timestamp_ms(&rules), gettime_ms(), philo->philo_id, msg, COLOR_RESET);
	pthread_mutex_unlock(rules->writing_mutex);
	return	;
}

void print_death_log(t_philo *philo, char *msg,  char *state_colour)
{	
	t_rules *rules;
	
	rules = *(philo->rules);
	pthread_mutex_lock(rules->writing_mutex);
		printf("%s timestamp:%ld %ld philosopher %d %s %s\n", state_colour, timestamp_ms(&rules), gettime_ms(), philo->philo_id, msg, COLOR_RESET);
	pthread_mutex_unlock(rules->writing_mutex);
	return	;
}
