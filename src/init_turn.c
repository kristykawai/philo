/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_turn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:54:19 by kawai             #+#    #+#             */
/*   Updated: 2024/02/17 19:11:38 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_turn(t_rules **rules)
{
	(*rules)->turn_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if ((*rules)->turn_mutex == NULL)
		error_exit("fail to allocate memory for turn mutex.\n", rules);
	(*rules)->access_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if ((*rules)->access_mutex == NULL)
		error_exit("fail to allocate memory for access mutex.\n", rules);
	if (pthread_mutex_init((*rules)->turn_mutex, NULL) != 0)
		error_exit("turn mutex initialization failed.\n", rules);
	if (pthread_mutex_init((*rules)->access_mutex, NULL) != 0)
		error_exit("access mutex initialization failed.\n", rules);
}
