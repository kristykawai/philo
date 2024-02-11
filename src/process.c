/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawai <kawai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:31:40 by kchan             #+#    #+#             */
/*   Updated: 2024/02/11 22:44:16 by kawai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(pthread_mutex_t *mutex)
{
	int i;
    int mails = 0;
    
	i = 0;
	while(i < 10000000)
	{
		pthread_mutex_lock(mutex);
		i++;
		mails++;
		pthread_mutex_unlock(mutex);
		// read mails
		// increment
		// write mails
	}
	printf("print mail num:%d\n", mails);
	return(0);
}

// void* philosopher_routine(void *arg) {
//     // Placeholder for the philosopher routine logic
//     t_rules *philosopher_rules = (t_rules*)arg;

//     // In a real scenario, you would include the logic for picking up and putting down forks,
//     // eating, and sleeping, in a loop until a certain condition is met.

//     // For example:
//     while (/* some condition */) {
//         // Pick up forks (lock mutexes)
//         // ...

//         // Eat
//         // ...

//         // Put down forks (unlock mutexes)
//         // ...

//         // Sleep
//         // ...
//     }

//     return NULL;
// }



// printf("Thread %d has started\n", i);
// pthread_join(th[i], NULL);
// printf("Thread %d has finished\n", i);
// 	printf("processed time in millisecond: %ld",(long)processed_time);
