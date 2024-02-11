/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rules.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:11:31 by kchan             #+#    #+#             */
/*   Updated: 2024/02/11 23:06:17 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	rules_value_check(t_rules **rules, char **argv)
{
	if ((*rules)->philo_number <= 0 || (*rules)->t_rule_die <= 0 
		|| (*rules)->t_rule_eat <= 0 || (*rules)->t_rule_sleep <= 0)
		{
			printf("Error: Only positive numbers are allowed for arguments 1 to 4.\n");
			return (0);
		}
	if	(argv[5] != NULL && (*rules)->min_eat_count <= 0)
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
	(*rules)->min_eat_count = -1;
	(*rules)->philo_number = atoi(argv[1]);
	(*rules)->t_rule_die = atoi(argv[2]);
	(*rules)->t_rule_eat = atoi(argv[3]);
	(*rules)->t_rule_sleep = atoi(argv[4]);
	if	(argv[5] != NULL)
		(*rules)->min_eat_count = atoi(argv[5]);
	if(!rules_value_check(rules, argv))
		return (-1);
	(*rules)->t_sim_start = gettime_ms();
	return(0);
}

void	create_philo_thread(t_rules **rules)
{
	pthread_t thread[(*rules)->philo_number];
	int	i;
	
	i = 0;
	while(i < (*rules)->philo_number)
	{
	if (pthread_create(&thread[i], 
		NULL, routine(&(*rules)->fork[i]), NULL) != 0)
		error_exit("thread creation failed.\n", rules);
		i++;
	}
}

void	init_sim_time(t_rules ** rules)
{
	time_t creation_time;

	creation_time = gettime_ms(); 
	if(creation_time == -1)
		error_exit("creation time failed.\n", rules);
	(*rules)->t_sim_start = creation_time;
}

int	init_all(t_rules **rules, char **argv)
{
	if(init_rules(rules, argv) == -1)
		return(-1);
	init_fork(rules);
	create_philo_thread(rules);
	init_sim_time(rules);
	// printf("sim start time%ld\n",(*rules)->t_sim_start);
	return(0);
}
