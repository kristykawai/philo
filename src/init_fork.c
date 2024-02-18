/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 22:38:51 by kawai             #+#    #+#             */
/*   Updated: 2024/02/18 19:36:12 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int int_fork_state_value(t_rules **rules)
{
	int fork_number;

	fork_number = (*rules)->philo_number;
	(*rules)->fork_state = (int *)malloc(sizeof(int) * fork_number);
	if ((*rules)->fork_state == NULL)
	{
		printf("ERROR: fail to allocate memory for fork_state.\n");
		return (-1);
	}
	memset((*rules)->fork_state, 0, fork_number * sizeof(int));
	return (0);
}

int int_fork_mutex(t_rules **rules)
{
	int i;

	i = 0;
	(*rules)->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (*rules)->philo_number);
	if ((*rules)->fork == NULL)
	{
		printf("ERROR: fail to allocate memory for fork mutex.\n");
		return (-1);
	}
	while(i < (*rules)->philo_number)
	{
		if(pthread_mutex_init(&(*rules)->fork[i], NULL) != 0)
			{
				printf("ERROR: fail initialize fork mutex.\n");
				return (-1);
			}
		i++;	
	}
	return(0);
}
 
void	init_fork(t_rules **rules)
{
	if(int_fork_state_value(rules) == -1)
		error_exit("fork state value initialization failed.\n", rules);
	if(int_fork_mutex(rules) == -1)
		error_exit("initialize mutex for fork failed.\n", rules);
}
