/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:41:19 by kawai             #+#    #+#             */
/*   Updated: 2024/02/23 11:43:28 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void free_mutex(pthread_mutex_t *mutex_ptr)
{
	free(mutex_ptr);
	mutex_ptr = NULL;
}

void destroy_mutexes(t_rules **rules)
{
	if((*rules)->access_mutex != NULL)
	{
		pthread_mutex_destroy((*rules)->access_mutex);
		free_mutex((*rules)->access_mutex);
		(*rules)->access_mutex = NULL;
	}
	if((*rules)->death_check_mutex != NULL)
	{
		pthread_mutex_destroy((*rules)->death_check_mutex);
		free_mutex((*rules)->death_check_mutex);
		(*rules)->death_check_mutex = NULL;
	}
	if((*rules)->writing_mutex != NULL)
	{
		pthread_mutex_destroy((*rules)->writing_mutex);
		free_mutex((*rules)->writing_mutex);
		(*rules)->writing_mutex = NULL;
	}
}

void destroy_mutexes_loop(t_rules **rules)
{
	int i;

	i = 0;
	if((*rules)->fork != NULL)
	{
		while(i < (*rules)->philo_number)
		{
			pthread_mutex_destroy(&(*rules)->fork[i]);
			i++;
		}
			free_mutex((*rules)->fork);
			(*rules)->fork = NULL;
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
	destroy_mutexes_loop(rules);
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
