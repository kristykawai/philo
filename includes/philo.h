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

typedef struct s_philo
{
	int philo_id;
	int left_fork_id;
	int right_fork_id;
	time_t t_last_meal;
	int meal_count;
	pthread_t	thread_id;
}t_philo;

typedef struct s_rules
{
	int philo_number;
	time_t time_rule_die;
	time_t time_rule_eat;
	time_t time_rule_sleep;
	int min_meal_count;
	time_t time_sim_start;
	int	*fork_state;
	pthread_mutex_t *fork;
	t_philo *philo;
}t_rules;

//init_fork.c
int		int_fork_state_value(t_rules **rules);
int		int_fork_mutex(t_rules **rules);
void	init_fork(t_rules **rules);

//init_rules.c
int		rules_value_check(t_rules **rules, char **argv);
int		init_rules(t_rules **rules, char **argv);
void	create_philo_thread(t_rules **rules);
int		init_all(t_rules ** rules, char **argv);

// int		init_fork(pthread_mutex_t *mutex_fork);
//time.c
void	init_sim_time(t_rules ** rules);
long	gettime_ms(void);

//process.c
void	*thread_create_process(void *mutex);

//clean.c
void	cleanup_rules(t_rules **rules);
void	error_exit(char * error_msg, t_rules **rules);
