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
	int right_fork_id;
	int left_fork_id;
	time_t t_last_eat;
	int eat_count;
} t_philo;

typedef struct s_rules
{
	int philo_number;
	time_t t_rule_die;
	time_t t_rule_eat;
	time_t t_rule_sleep;
	int min_eat_count;
	time_t t_sim_start;
	int	*fork_state;
	pthread_mutex_t *fork;
}t_rules;

//init_fork.c
int		int_fork_state_value(t_rules **rules);
int		int_fork_mutex(t_rules **rules);
void	init_fork(t_rules **rules);

//init_rules.c
int		rules_value_check(t_rules **rules, char **argv);
int		init_rules(t_rules **rules, char **argv);
void	create_philo_thread(t_rules **rules);
void	init_sim_time(t_rules ** rules);
int		init_all(t_rules ** rules, char **argv);

// int		init_fork(pthread_mutex_t *mutex_fork);
//time.c
long	gettime_ms(void);

//process.c
void	*routine(pthread_mutex_t *mutex);

//clean.c
void	cleanup_rules(t_rules **rules);
void	error_exit(char * error_msg, t_rules **rules);
