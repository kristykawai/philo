#include "philo.h"


int main(int argc, char *argv[])
{
	t_rules	*rules;
	int ret;

	rules = (t_rules *)malloc(sizeof(t_rules));
	if(rules == NULL)
		printf("ERROR: memory allocation for rule structure failed.");
	ret = -1;
	if (argc == 5 || argc == 6)
		ret = init_rules(&rules, argv);
	if (ret == -1)
	{
		printf("ERROR: memory allocation for rule structure failed.");
		free(rules);
		return (-1);
	}
	free(rules);
	return (0);
}
