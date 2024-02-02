#include "philo.h"
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/syscall.h>

int mails = 0;
pthread_mutex_t mutex;


void	*routine()
{
	int i;

	i = 0;
	while(i < 10000000)
	{
		pthread_mutex_lock(&mutex);
		i++;
		mails++;
		pthread_mutex_unlock(&mutex);
		// read mails
		// increment
		// write mails
	}
	// printf("print mail num:%d\n", mails);
	return(0);
}

int main()
{
	pthread_t th[PHILO_NUM];
	pthread_mutex_init(&mutex, NULL);
	int	i;

	i = 0;
	while(i < PHILO_NUM)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			perror("Failed to create thread");
		}
		printf("Thread %d has started\n", i);
		pthread_join(th[i], NULL);
		printf("Thread %d has finished\n", i);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("print mail num:%d\n", mails);
	return (0);
}
