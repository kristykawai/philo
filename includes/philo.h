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


/*
philo_id starts at 1.
fork_id starts at 1.
clockwise opertation for processing. 
except for the last philo,
for each philo, left fork is to its left facing the table, left fork id is philo_id.
for each philo, right fork is to its right facing the table, right fork id is philo_id -1.
last philo left fork id is the start of the fork index.
e.g. 5 philo
philo id:5
left fork id: 1
right fork id: 4
*/

typedef struct s_philo
{
	int philo_id;
	int left_fork_id;
	int right_fork_id;
	time_t time_last_meal;
	time_t time_creation;
	int meal_count;
	pthread_t	thread_id;
	struct s_rules **rules;
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
int		init_param(t_rules **rules, char **argv);
void	*test(void *philo_ptr);
// int		init_fork(pthread_mutex_t *mutex_fork);
//time.c
void	init_sim_time(t_rules ** rules);
long	gettime_ms(void);

//engine.c
// void *routine(void *arg);
void	engine(t_rules **rules);
void	create_philo_thread(t_rules **rules);
void	*test(void *philo_ptr);
void	philo_pthread_join(t_rules **rules);

//clean.c
void	cleanup_rules(t_rules **rules);
void	error_exit(char * error_msg, t_rules **rules);


