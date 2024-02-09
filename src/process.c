/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:31:40 by kchan             #+#    #+#             */
/*   Updated: 2024/02/09 17:44:42 by kchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

		// printf("Thread %d has started\n", i);
		// pthread_join(th[i], NULL);
		// printf("Thread %d has finished\n", i);

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
