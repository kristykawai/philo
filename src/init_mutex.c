/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:59:27 by kawai             #+#    #+#             */
/*   Updated: 2024/03/01 15:11:15 by kchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_access(t_rules **rules)
{
	(*rules)->access_mutex = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t));
	if ((*rules)->access_mutex == NULL)
		error_exit("fail to allocate memory for access mutex.\n", rules);
	if (pthread_mutex_init((*rules)->access_mutex, NULL) != 0)
		error_exit("access mutex initialization failed.\n", rules);
}

void	init_death_check(t_rules **rules)
{
	(*rules)->death_check_mutex = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t));
	if ((*rules)->death_check_mutex == NULL)
		error_exit("fail to allocate memory for death check mutex.\n", rules);
	if (pthread_mutex_init((*rules)->death_check_mutex, NULL) != 0)
		error_exit("death check initialization failed.\n", rules);
}

void	init_write(t_rules **rules)
{
	(*rules)->writing_mutex = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t));
	if ((*rules)->writing_mutex == NULL)
		error_exit("fail to allocate memory for writing mutex.\n", rules);
	if (pthread_mutex_init((*rules)->writing_mutex, NULL) != 0)
		error_exit("writing mutex initialization failed.\n", rules);
}
