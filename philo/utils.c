#include "include/philo.h"

long	ft_atoi(const char *str)
{
	long	res;
	long	sign;
	long	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

int ft_len_arr(char **av)
{
	int i;

	i = 1;
	while(av[i])
	{
		i++;
	}
	return (i);
}

long timestamp_in_ms() {
    struct timeval time;

    gettimeofday(&time, NULL);
    long milliseconds = time.tv_sec * 1000 + time.tv_usec / 1000;
    return (milliseconds);
}

