/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:41:19 by kawai             #+#    #+#             */
/*   Updated: 2024/02/17 19:00:14 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void destroy_mutexes(t_rules **rules)
{
	int i;

	i = 0;
	if((*rules)->fork != NULL)
	{
		while(i < (*rules)->philo_number)
			pthread_mutex_destroy(&(*rules)->fork[i]);
		free((*rules)->fork);
		(*rules)->fork = NULL;
		i++;
	}
	if((*rules)->turn_mutex != NULL)
	{
		pthread_mutex_destroy((*rules)->turn_mutex);
		free((*rules)->turn_mutex);
		(*rules)->turn_mutex = NULL;
	}
	if((*rules)->access_mutex != NULL)
	{
		pthread_mutex_destroy((*rules)->access_mutex);
		free((*rules)->access_mutex);
		(*rules)->access_mutex = NULL;
	}
}

void cleanup_rules(t_rules **rules)
{
    if((*rules)->fork_state != NULL)
	{
		free((*rules)->fork_state);
		(*rules)->fork_state = NULL;
	}
	if ((*rules)->philo != NULL)
	{
		free((*rules)->philo);
		(*rules)->philo = NULL;
	}
	destroy_mutexes(rules);
	if((*rules)!= NULL)
	{
		free(*rules);
		*rules = NULL;
	}
}

void	error_exit(char * error_msg, t_rules **rules)
{
	printf("ERROR:%s", error_msg);
	cleanup_rules(rules);
	exit(-1);
}
