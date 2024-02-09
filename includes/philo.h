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
	pthread_mutex_t *fork;
}t_rules;

//init.c
int		init_rules(t_rules **rules, char **argv);
int		init_fork(pthread_mutex_t *mutex_fork);

//time.c
long	gettime_ms(void);

//process.c
void	*routine(pthread_mutex_t *mutex);
