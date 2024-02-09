/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:11:31 by kchan             #+#    #+#             */
/*   Updated: 2024/02/09 18:07:58 by kchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_rules(t_rules **rules, char **argv)
{
	if( rules == NULL || *rules == NULL)
		return (-1);
	(*rules)->philo_number = atoi(argv[1]);
	(*rules)->t_rule_die = atoi(argv[2]);
	(*rules)->t_rule_eat = atoi(argv[3]);
	(*rules)->t_rule_sleep = atoi(argv[4]);
	if	(argv[5] != NULL)
		(*rules)->min_eat_count = atoi(argv[5]);
	(*rules)->t_sim_start = gettime_ms();
	return(0);
}

int	init_fork(pthread_mutex_t *mutex_fork)
{
	pthread_mutex_init(mutex_fork, NULL);
	return(0);
}

void	thread_creation(t_rules **rules)
{
	pthread_t thread[(*rules)->philo_number];
	int	i;
	time_t creation_time;

	creation_time = gettime_ms(); 
	if(creation_time == -1)
		perror("can't get current time");
	i = 0;
	while(i < (*rules)->philo_number)
	{
	if (init_fork(&(*rules)->fork[i]) != 0)
		perror("Failed to initialize mutex for fork");
	if (pthread_create(&thread[i], NULL, routine(&(*rules)->fork[i]), NULL) != 0)
		perror("Failed to create thread");
		i++;
	}
}


// 	pthread_mutex_destroy(&mutex);
// 	printf("print mail num:%d\n", mails);
// 	end_time = gettime();
// 	processed_time = end_time - start_time;
// 	printf("processed time in millisecond: %ld",(long)processed_time);




