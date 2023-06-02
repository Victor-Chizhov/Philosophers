#include "include/philo.h"

int check_arguments(char **av)
{
	int i;
	int j;
	int check;

	i = 1;
	check = 0;
	while(av[i])
	{
		j = 0;
		while(av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				check++;
			j++;
		}
		i++;
	}
	if (check)
		return 0;
	if(av[5])
		if(ft_atoi(av[5]) == 0)
			return 0;
	return 1;
}