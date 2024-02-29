/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rules.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:11:31 by kchan             #+#    #+#             */
/*   Updated: 2024/02/29 23:21:38 by kawai            ###   ########.fr       */
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
	if (argv[5] != NULL && (*rules)->min_meal_count <= 0)
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
	(*rules)->current_turn = 0;
	(*rules)->total_meal_count = 0;
	(*rules)->philo_die = 0;
	(*rules)->time_death = 0;
	(*rules)->meal_stop = 0;
	(*rules)->death_check_done = 0;
	return(0);
}

void init_access(t_rules **rules)
{
	(*rules)->access_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if ((*rules)->access_mutex == NULL)
		error_exit("fail to allocate memory for access mutex.\n", rules);
	if (pthread_mutex_init((*rules)->access_mutex, NULL) != 0)
		error_exit("access mutex initialization failed.\n", rules);
}

void init_death_check(t_rules **rules)
{
	(*rules)->death_check_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if ((*rules)->death_check_mutex == NULL)
		error_exit("fail to allocate memory for death check mutex.\n", rules);
	if (pthread_mutex_init((*rules)->death_check_mutex, NULL) != 0)
		error_exit("death check initialization failed.\n", rules);
}

void init_write(t_rules **rules)
{
	(*rules)->writing_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if ((*rules)->writing_mutex == NULL)
		error_exit("fail to allocate memory for writing mutex.\n", rules);
	if (pthread_mutex_init((*rules)->writing_mutex, NULL) != 0)
		error_exit("writing mutex initialization failed.\n", rules);
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
		(*rules)->philo[i].philo_id = i + 1;
		(*rules)->philo[i].left_fork_id = -1;	
		(*rules)->philo[i].right_fork_id = -1;
		(*rules)->philo[i].time_last_meal = 0;	
		(*rules)->philo[i].time_creation = 0;	
		(*rules)->philo[i].time_death = 0;	
		(*rules)->philo[i].meal_count = 0;	
		(*rules)->philo[i].rules = rules;
		(*rules)->philo[i].is_alive = 1;
		i++;
	}
}

int	init_param(t_rules **rules, char **argv)
{
	if(init_rules(rules, argv) == -1)
		return(-1);
	init_death_check(rules);
	init_write(rules);
	init_access(rules);
	init_fork(rules);
	init_philo(rules);
	init_sim_time(rules);
	return(0);
}
