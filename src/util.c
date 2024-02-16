/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:38:10 by kchan             #+#    #+#             */
/*   Updated: 2024/02/16 23:17:15 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_log(t_rules *rules, char *msg)
{
	printf("%ld philosopher %d %s\n", gettime_ms(), rules->philo->philo_id, msg);
}