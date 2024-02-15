/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:59:26 by kawai             #+#    #+#             */
/*   Updated: 2024/02/15 17:10:21 by kchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
	t_rules	*rules;
	int ret;

	ret = -1;
	rules = (t_rules *)malloc(sizeof(t_rules));
	if(!rules)
		error_exit("Memory allocation for rule structure failed.\n", &rules);
	if (argc == 5 || argc == 6)
	{
		ret = init_all(&rules, argv);
		if(ret == -1)
		{
			free(rules);
			error_exit("initilization failed.\n", &rules);
		}
		cleanup_rules(&rules);
	}
	return (0);
}
