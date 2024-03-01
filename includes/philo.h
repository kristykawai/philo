/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:00:11 by kawai             #+#    #+#             */
/*   Updated: 2024/03/01 15:09:40 by kchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>

#define COLOR_RESET "\033[0m"
#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define CYAN "\033[1;36m"
#define MAGENTA "\033[1;35m"
#define WHITE "\033[1;37m"

typedef struct s_philo
{
	int				philo_id;
	int				left_fork_id;
	int				right_fork_id;
	time_t			time_last_meal;
	time_t			time_creation;
	time_t			time_death;
	int				meal_count;
	pthread_t		thread_id;
	pthread_t		thread_monitor_id;
	struct s_rules	**rules;
	int				is_alive;
}	t_philo;

typedef struct s_rules
{
	int					philo_number;
	time_t				time_rule_die;
	time_t				time_rule_eat;
	time_t				time_rule_sleep;
	int					min_meal_count;
	time_t				time_sim_start;
	int					*fork_state;
	pthread_mutex_t		*fork;
	t_philo				*philo;
	int					current_turn;
	int					total_meal_count;
	int					philo_die;
	time_t				time_death;
	int					meal_stop;
	pthread_mutex_t		*access_mutex;
	pthread_mutex_t		*death_check_mutex;
	pthread_mutex_t		*writing_mutex;
}	t_rules;

//init_fork.c
int		int_fork_state_value(t_rules **rules);
int		int_fork_mutex(t_rules **rules);
void	init_fork(t_rules **rules);

//init_mutex.c
void	init_access(t_rules **rules);
void	init_death_check(t_rules **rules);
void	init_write(t_rules **rules);

//init_rules.c
int		rules_value_check(t_rules **rules, char **argv);
int		init_rules(t_rules **rules, char **argv);
void	create_philo_thread(t_rules **rules);
int		init_param(t_rules **rules, char **argv);

//time.c
void	init_sim_time(t_rules **rules);
long	gettime_ms(void);
void	sleep_with_timeout(long duration_ms);
long	timestamp_ms(t_rules **rules);

//engine.c
void	create_philo_thread(t_rules **rules);
void	philo_pthread_join(t_rules **rules);
void	engine(t_rules **rules);

//routine_philo.c
void	*routine(void *philo_ptr);

//routine_fork.c
int		find_available_fork(int *fork_state, int philo_nb);
int		check_assign_fork(t_philo *philo);
void	try_to_acquire_forks(t_philo *philo);
void	put_down_forks(t_philo *philo);
int		longest_wait_philo(t_philo *philo);

//process.c
int		death_check(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	eat_and_sleep_think(t_philo *philo);

//clean.c
void	free_mutex(pthread_mutex_t *mutex_ptr);
void	destroy_mutexes(t_rules **rules);
void	destroy_mutexes_loop(t_rules **rules);
void	cleanup_rules(t_rules **rules);
void	error_exit(char *error_msg, t_rules **rules);

//util.c
void	print_log(t_philo *philo_ptr, char *msg, char *state_colour);
void	print_death_log(t_philo *philo, char *msg, char *state_colour);
void	*latest_eat_philo(t_philo *philo);
void	print_exit_condition_lancher_log(t_rules **rules);

//monitor.c
void	*monitor_routine(void *philo_ptr);
void	create_monitor_thread(t_rules **rules);
void	*find_death(t_philo *philo);
int		check_eat_min(t_philo *philo);