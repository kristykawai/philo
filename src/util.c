/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:38:10 by kchan             #+#    #+#             */
/*   Updated: 2024/02/17 19:06:59 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	count_odd_numbers(int total_nb)
{
	int total_odd_numbers;
	
	total_odd_numbers = 0;
	if (total_nb == 1)
		return (1);
	total_odd_numbers = (total_nb + 1) / 2;
	return (total_odd_numbers);
}

void print_log(t_philo *philo, char *msg)
{
	printf("%ld philosopher %d %s\n", gettime_ms(), philo->philo_id, msg);
}
