#include "include/philo.h"

int init_struct_philo(t_info *info, char **av)
{
	int i;

	i = 0;
	info->number_of_philosophers = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	info->death = 0;
	if (av[5])
		info->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		info->number_of_times_each_philosopher_must_eat = 0;
	info->philo = malloc(sizeof(t_philo) * info->number_of_philosophers);
	if (!info->philo)
		return 0;
	while(i < info->number_of_philosophers)
	{
		info->philo[i].id = i + 1;
		info->philo[i].left = i;
		info->philo[i].right = i + 1;
		info->philo[i].info = info;
		info->philo[i].count_eat = 0;
		info->philo[i].last_eating = 0;
		i++;
	}
	info->philo[i - 1].right = 0;
	
	return 1;
}

int init_struct_mutex(t_info *info)
{
	int i;

	i = 0;
	if(pthread_mutex_init(&info->wait, NULL))
		return 0;
	if(pthread_mutex_init(&info->for_check, NULL))
		return 0;
	info->mutex = malloc(sizeof(pthread_mutex_t) * info->number_of_philosophers);
	if (!info->mutex)
		return 0;
	while(i < info->number_of_philosophers)
	{
		if(pthread_mutex_init(&info->mutex[i], NULL))
			return 0;
		i++;
	}
	return 1;
}

