/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:38:10 by kchan             #+#    #+#             */
/*   Updated: 2024/03/01 23:41:58 by kawai            ###   ########.fr       */
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

void	print_exit_condition_launcher_log(t_rules **rules)
{
	if ((*rules)->meal_stop)
	{
		print_death_log(latest_eat_philo((*rules)->philo),
			"finished meal. Meal stop condition reached.", RED);
		cleanup_rules(rules);
		exit(0);
	}
	if ((*rules)->philo_die)
		error_exit("philo die\n", rules);
}
