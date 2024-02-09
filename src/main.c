#include "philo.h"

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

int	gettime()
{
	struct  timeval current_time;
	time_t current_time_ms;

	if(gettimeofday(&current_time, NULL) != 0)
		return(-1);
	current_time_ms = current_time.tv_sec * 1000 + current_time.tv_usec/1000;
	printf("millisecond: %ld\n",(long)current_time.tv_usec);
	return(current_time_ms);
}

int main()
{
	pthread_t th[PHILO_NUM];
	pthread_mutex_init(&mutex, NULL);
	int	i;
	time_t start_time;
	time_t end_time;
	time_t processed_time;

	i = 0;
	start_time = gettime(); 
	if(start_time == -1)
		perror("can't get current time");
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
	end_time = gettime();
	processed_time = end_time - start_time;
	printf("processed time in millisecond: %ld",(long)processed_time);
	return (0);
}
