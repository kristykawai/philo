/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:38:10 by kchan             #+#    #+#             */
/*   Updated: 2024/03/01 14:42:48 by kchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(t_philo *philo, char *msg, char *state_colour)
{
	t_rules	*rules;

	rules = *(philo->rules);
	pthread_mutex_lock(rules->writing_mutex);
	if (!rules->philo_die && rules->meal_stop != 1)
		printf("%s%ld %d %s%s\n",
			state_colour, timestamp_ms(&rules),
			philo->philo_id, msg, COLOR_RESET);
	pthread_mutex_unlock(rules->writing_mutex);
	return ;
}

void	print_death_log(t_philo *philo, char *msg, char *state_colour)
{
	t_rules	*rules;

	rules = *(philo->rules);
	pthread_mutex_lock(rules->writing_mutex);
	printf("%s%ld %d %s%s\n",
		state_colour, timestamp_ms(&rules), philo->philo_id, msg, COLOR_RESET);
	pthread_mutex_unlock(rules->writing_mutex);
	return ;
}

void	*latest_eat_philo(t_philo *philo)
{
	t_rules		*rules;
	long		latest_meal_time;
	int			i;
	int			j;

	latest_meal_time = INT64_MIN;
	j = -1;
	i = 0;
	rules = *(philo->rules);
	while (i < rules->philo_number)
	{
		if (rules->philo[i].time_last_meal > latest_meal_time)
		{
			latest_meal_time = rules->philo[i].time_last_meal;
			j = i;
		}
		i++;
	}
	return (&rules->philo[j]);
}

void	print_exit_condition_lancher_log(t_rules **rules)
{
	int	termination_message_printed;

	termination_message_printed = 0;
	if ((*rules)->philo_die || (*rules)->meal_stop)
	{
		if (!termination_message_printed)
		{
			if ((*rules)->philo_die)
			{
				print_death_log(find_death((*rules)->philo),
					"death program exit time", RED);
				error_exit("one philo died. simulation stop\n", rules);
			}
			else
			{
				print_death_log(latest_eat_philo((*rules)->philo),
					"finished meal. Meal stop condition reached.", RED);
				termination_message_printed = 1;
				cleanup_rules(rules);
				exit(0);
			}
		}
	}
}
