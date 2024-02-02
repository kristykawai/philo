//#include "../includes/philo.h"
#include "philo.h"

void	*routine()
{
	printf("Test from threads\n");
	return (0);
}

int main()
{
	pthread_t t1;

	pthread_create(&t1, NULL, &routine, NULL);
	pthread_join(t1, NULL);
	return (0);
}