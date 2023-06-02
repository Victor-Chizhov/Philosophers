#include "include/philo.h"

void	my_sleep(long ms)
{
	long	t;

	t = timestamp_in_ms();
	while (timestamp_in_ms() - t < ms)
		usleep(1);
}

void ft_print(char *str, t_philo *philo, int id)
{
	if (philo->info->stop_print != 1)
	{
		pthread_mutex_lock(&philo->info->wait);
		printf("%ld %d %s\n", timestamp_in_ms() - philo->info->start_time, id, str);
		pthread_mutex_unlock(&philo->info->wait);
	}

}

void philo_sleep_and_think_print(t_philo *philo)
{
	if(philo->info->death != 1)
	{
		ft_print("is sleeping", philo, philo->id);
		my_sleep(philo->info->time_to_sleep);
		ft_print("is thinking", philo, philo->id);
	}	
}

void *check_of_death_philo(void *data)
{
	t_info *info;
	int i;
	long current_time;
	info = (t_info *)data;
	
	while(info->death != 1)
	{
		i = 0;
		while(i < info->number_of_philosophers)
		{
			if (info->stop_print != 1)
			{
				current_time = timestamp_in_ms() - info->start_time;
				//pthread_mutex_lock(&info->for_check);
				if ((current_time - info->philo[i].last_eating) > info->time_to_die)
				{
					//pthread_mutex_unlock(&info->for_check);
					ft_print("died", &info->philo[i], info->philo[i].id);
					info->death = 1;
					info->stop_print = 1;
					break;
				}
				//pthread_mutex_unlock(&info->for_check);
				
			}
			i++;
		}
        if (info->all_stop)
            break;
	}
	return NULL;
}


int philo_eat(t_philo *philo)
{

	int left;
	int right;

	if(philo->info->number_of_philosophers == 1)
	{
		my_sleep(philo->info->time_to_die);
		return 0;
	}

	left = philo->left;
	right = philo->right;
	pthread_mutex_lock(&philo->info->mutex[left]);
	pthread_mutex_lock(&philo->info->mutex[right]);
		
	ft_print("has taken a fork", philo, philo->id);
	ft_print("is eating", philo, philo->id);	
	philo->last_eating = timestamp_in_ms() - philo->info->start_time;
	my_sleep(philo->info->time_to_eat);
	philo->count_eat++;
	pthread_mutex_unlock(&philo->info->mutex[left]);
	pthread_mutex_unlock(&philo->info->mutex[right]);

	return 1;
}


void *livephilo(void *data)
{
	int i;
	t_philo *philo;	
	
	i = 0;
	philo = (t_philo *)data;
	//pthread_mutex_lock(&philo->info->for_check);
	philo->last_eating = timestamp_in_ms() - philo->info->start_time;
	//pthread_mutex_unlock(&philo->info->for_check);
	if (philo->id % 2 == 0)
		usleep(2500);
	while(philo->info->death != 1)
	{
		if(!philo_eat(philo))
			return NULL;
		if (philo->count_eat == philo->info->number_of_times_each_philosopher_must_eat)
		{
			philo->info->all_stop = 1;
			//philo->info->death = 1;
			return NULL;
		}
		if (philo->info->death != 1)
		{
			philo_sleep_and_think_print(philo);
		}
	}
	return NULL;
}

void mutex_destroy(t_info *info)
{
	int i;

	i = 0;
	pthread_mutex_destroy(&info->wait);
	pthread_mutex_destroy(&info->for_check);
	while(i < info->number_of_philosophers)
	{
		pthread_mutex_destroy(&info->mutex[i]);
		i++;
	}
	free(info->mutex);
	free(info->philo);
}

int init_pthread_philo(t_info *info)
{
	int i;

	i = 0;
	info->start_time = timestamp_in_ms();
	info->stop_print = 0;
	info->all_stop = 0;
	
	if (pthread_create(&info->check_of_death, NULL, &check_of_death_philo, (void *)info))
		return 0;
	
	while(i < info->number_of_philosophers)
	{
		if (pthread_create(&info->philo[i].pthr, NULL, &livephilo, &info->philo[i]))
			return 0;
		i++;
	} 
	if (pthread_join(info->check_of_death, NULL))
		return 0;
	i = 0;
	while(i < info->number_of_philosophers)
	{
		if (pthread_join(info->philo[i].pthr, NULL))
			return 0;
		i++;
	}
	return (1);
}


int main(int ac, char **av)
{
	t_info info;

	if (ac == 5 || ac == 6)
	{
		if (!check_arguments(av))
		{
			printf("Arguments not valided!\n");
			return 0;
		}
		if (!init_struct_philo(&info, av))
			return 0;
		if (!init_struct_mutex(&info))
			return 0;
		if (!init_pthread_philo(&info))
			return 0;
		mutex_destroy(&info);
	}
	else
	{
		printf("Error\n");
	}
}