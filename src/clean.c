/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:41:19 by kawai             #+#    #+#             */
/*   Updated: 2024/02/16 15:38:26 by kchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void cleanup_rules(t_rules **rules)
{
	int i;

	i = -1;
    if((*rules)->fork_state != NULL)
	{
		free((*rules)->fork_state);
		(*rules)->fork_state = NULL;
	}
	if((*rules)->fork != NULL)
	{
		while(++i < (*rules)->philo_number)
			pthread_mutex_destroy(&(*rules)->fork[i]);
		free((*rules)->fork);
		(*rules)->fork = NULL;
	}
	if ((*rules)->philo != NULL)
	{
		free((*rules)->philo);
		(*rules)->philo = NULL;
	}
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
