#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

struct s_info;

typedef struct s_philo {

	struct s_info *info;
	pthread_t pthr;
	int left;
	int right;
	int id;
	long last_eating;
	int eat_now;
	long current_time;
	long count_eat;
	

} t_philo;

typedef struct s_info {
	
	t_philo *philo;
	pthread_mutex_t *mutex;
	pthread_mutex_t wait;
	pthread_mutex_t for_check;
	long number_of_philosophers;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	long number_of_times_each_philosopher_must_eat;
	long start_time;
	pthread_t check_of_death;
	int death;
	int stop_print;
	int all_stop;
	

} t_info;




//================= UTILS =============================

long	ft_atoi(const char *str);
int ft_len_arr(char **av);


int check_arguments(char **av);


int init_struct_philo(t_info *info, char **av);
int init_struct_mutex(t_info *info);
long timestamp_in_ms();

#endif