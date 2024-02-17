/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:59:26 by kawai             #+#    #+#             */
/*   Updated: 2024/02/17 19:12:31 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
	t_rules	*rules;
	int ret;

	if (argc != 5 && argc != 6 )
	{
		printf("Usage : ./philo nb_philos time_die time_eat time_sleep");
		printf("[nb_time_each_philo_must_eat]\n");
		return (-1);
	}
	if (argc == 5 || argc == 6)
	{
		ret = -1;
		rules = (t_rules *)malloc(sizeof(t_rules));
		if(!rules)
			error_exit("Memory allocation for rule structure failed.\n", &rules);
		ret = init_param(&rules, argv);
		if(ret == -1)
			error_exit("initilization failed.\n", &rules);
		engine(&rules);
		cleanup_rules(&rules);
	}
	return (0);
}
