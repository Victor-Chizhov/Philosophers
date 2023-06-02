#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;

int x = 0;

void ft_print1()
{
	//3 блокируем мьютекс
	pthread_mutex_lock(&mutex);


	int i = 0;
	while(i < 10000000)
	{
		x++;
		i++;
	}
	//4 разблокируем мьютекс
	pthread_mutex_unlock(&mutex);
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	pthread_t t1, t2;
	//1 инициализация
	pthread_mutex_init(&mutex, NULL);

	if(pthread_create(&t1, NULL, (void *)ft_print1, NULL))
		return 1;
	if(pthread_create(&t2, NULL, (void *)ft_print1, NULL))
		return 2;
	if(pthread_join(t1, NULL))
		return 3;
	if(pthread_join(t2, NULL))
		return 4;
	
	//2 очистка (удаление) мьютекса
	pthread_mutex_destroy(&mutex);
	
	
	printf("x = %d\n", x);

	return 0;
}