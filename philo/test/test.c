#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int x = 2;

void *ft_print1()
{
	x++;
	sleep(1);
	printf("Test from thread %d\n", x);
	return NULL;
}

void *ft_print2()
{
	x += 5;
	sleep(1);
	printf("Test from thread %d\n", x);
	return NULL;
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	pthread_t t1, t2;
	if(pthread_create(&t1, NULL, &ft_print1, NULL))
		return 1;
	if(pthread_create(&t2, NULL, &ft_print2, NULL))
		return 2;
	if(pthread_join(t1, NULL))
		return 3;
	if(pthread_join(t2, NULL))
		return 4;
	return 0;
}