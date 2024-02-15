/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rules.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:11:31 by kchan             #+#    #+#             */
/*   Updated: 2024/02/16 00:00:52 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	rules_value_check(t_rules **rules, char **argv)
{
	if ((*rules)->philo_number <= 0 || (*rules)->time_rule_die <= 0 
		|| (*rules)->time_rule_eat <= 0 || (*rules)->time_rule_sleep <= 0)
		{
			printf("Error: Only positive numbers are allowed for arguments 1 to 4.\n");
			return (0);
		}
	if	(argv[5] != NULL && (*rules)->min_meal_count <= 0)
		{
			printf("Error: Only positive numbers are allowed for number of times must eat.\n");
			return (0);
		}
	return (1);
}

int	init_rules(t_rules **rules, char **argv)
{
	if( rules == NULL || *rules == NULL)
		return (-1);
	(*rules)->min_meal_count = -1;
	(*rules)->philo_number = atoi(argv[1]);
	(*rules)->time_rule_die = atoi(argv[2]);
	(*rules)->time_rule_eat = atoi(argv[3]);
	(*rules)->time_rule_sleep = atoi(argv[4]);
	if	(argv[5] != NULL)
		(*rules)->min_meal_count = atoi(argv[5]);
	if(!rules_value_check(rules, argv))
		return (-1);
	(*rules)->time_sim_start = gettime_ms();
	return(0);
}

void	create_philo_thread(t_rules **rules)
{
	int i;

	i = 0;
	while(i < (*rules)->philo_number)
	{
		pthread_create(&(*rules)->philo[i].thread_id, 
			NULL, thread_create_process, (void *)&(*rules)->philo[i]);
		printf("index:%d\n",i);
		i++;
	}
}

void	init_philo(t_rules **rules)
{
	int	i;

	(*rules)->philo = malloc((*rules)->philo_number * sizeof(t_philo));
	if(!(*rules)->philo)
		error_exit("failed to allocate memory for philo", rules);
	i = 0;
	while(i < (*rules)->philo_number)
	{
		(*rules)->philo[i].philo_id = i;
		(*rules)->philo[i].left_fork_id = i;	
		(*rules)->philo[i].right_fork_id = i + 1;
		(*rules)->philo[i].t_last_meal = 0;	
		(*rules)->philo[i].meal_count = -1;	
		i++;
	}
	(*rules)->philo[i-1].left_fork_id  = 0;
}

int	init_all(t_rules **rules, char **argv)
{
	if(init_rules(rules, argv) == -1)
		return(-1);
	init_fork(rules);
	init_philo(rules);
	create_philo_thread(rules);
	init_sim_time(rules);
	return(0);
}



//backup

// void	create_philo_thread(t_rules **rules)
// {
// 	pthread_t thread[(*rules)->philo_number];
// 	int	i;
	
// 	i = 0;
// 	while(i < (*rules)->philo_number)
// 	{
// 	if (pthread_create(&thread[i], 
// 		NULL, routine(&(*rules)->fork[i]), NULL) != 0)
// 		error_exit("thread creation failed.\n", rules);
// 		i++;
// 	}
// }