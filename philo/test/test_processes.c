#include <stdio.h>
#include <unistd.h>

int main()
{
	int id = fork();
	if (id == 0)
		printf("Hello, I'm child\n");
	else
		printf("Hello, I'm parant\n");
}


