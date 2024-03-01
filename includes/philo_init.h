/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:48:18 by kawai             #+#    #+#             */
/*   Updated: 2024/03/02 00:06:26 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_INIT_H
# define PHILO_INIT_H

# include "philo.h"

//init_rules.c
int		flag_decimal(const char *str);
int		rules_value_check(t_rules **rules, char **argv);
int		init_rules(t_rules **rules, char **argv);
void	init_philo(t_rules **rules);
int		init_param(t_rules **rules, char **argv);

//init_mutex.c
void	init_access(t_rules **rules);
void	init_death_check(t_rules **rules);
void	init_write(t_rules **rules);

//init_fork.c
int		int_fork_state_value(t_rules **rules);
int		int_fork_mutex(t_rules **rules);
void	init_fork(t_rules **rules);

#endif