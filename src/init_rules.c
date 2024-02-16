/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rules.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:11:31 by kchan             #+#    #+#             */
/*   Updated: 2024/02/16 14:08:49 by kchan            ###   ########.fr       */
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
		(*rules)->philo[i].left_fork_id = i + 1;	
		(*rules)->philo[i].right_fork_id = i; 
		(*rules)->philo[i].time_last_meal = 0;	
		(*rules)->philo[i].time_creation = 0;	
		(*rules)->philo[i].meal_count = -1;	
		(*rules)->philo[i].rules = rules;
		i++;
	}
	(*rules)->philo[i-1].left_fork_id  = 0;
}

void create_philo_thread(t_rules **rules)
{
    int i;

    i = 0;
    while (i < (*rules)->philo_number)
    {
        if (pthread_create(&(*rules)->philo[i].thread_id, 
            NULL, test, &(*rules)->philo[i]) != 0)
            error_exit("failed to create thread for a philo", rules);
        i++;
    }
}
void	*test(void *philo_ptr)
{
	t_philo *philo;
	t_rules *rules;
	
	philo = (t_philo *)philo_ptr;
    rules = (t_rules *)*philo->rules;
	// printf("test philo id:%d\n", philo->philo_id);
	// printf("address of rules:%p\n", philo->rules);
	if (philo->rules != NULL && *philo->rules != NULL) 
	{
		if (rules->fork_state != NULL && rules->fork_state[philo->left_fork_id] == 0) 
		{
			pthread_mutex_lock(&(rules->fork[philo->left_fork_id]));
			printf("left fork is available and locked\n");
			printf("left fork id:%d\n",philo->left_fork_id);
			printf("left fork is picked up by philo:%d\n",philo->philo_id);
			rules->fork_state[philo->left_fork_id] = 1;
			
			printf("right fork id:%d\n",philo->right_fork_id);
			if (rules->fork_state != NULL && rules->fork_state[philo->right_fork_id] == 0) 
			pthread_mutex_lock(&(rules->fork[philo->right_fork_id]));
			printf("right fork is available and locked\n");
			rules->fork_state[philo->right_fork_id] = 1;
			printf("right fork is picked up by philo:%d\n",philo->philo_id);
			printf("philo %d is eating\n",philo->philo_id);
		}
    }

	// printf("I am eating");
	return NULL;
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

// void	*thread_creation(void *philo_ptr)
// {
// 	// t_rules					*rules;
// 	t_philo *const	philo = (t_philo *)philo_ptr;
// 	// rules = philo->rules;
// 	printf("philo id:%d",philo->philo_id);
// 	return (NULL);
// }