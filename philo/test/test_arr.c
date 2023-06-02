#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;

int x = 0;

void ft_print1()
{
	pthread_mutex_lock(&mutex);
	int i = 0;
	while(i < 10000000)
	{
		x++;
		i++;
	}
	pthread_mutex_unlock(&mutex);

}


int main(int ac, char **av)
{

	pthread_t th_arr[100];

	pthread_mutex_init(&mutex, NULL);

	int i = 0;
	while(i < 100)
	{
		if(pthread_create(&th_arr[i], NULL, (void *)ft_print1, NULL))
			return 1;
		
		if(pthread_join(th_arr[i], NULL))
			return 1;
		i++;
		printf("count pthreads %d\n", i);
	}

	pthread_mutex_destroy(&mutex);
	printf("x = %d\n", x);

	return 0;
}