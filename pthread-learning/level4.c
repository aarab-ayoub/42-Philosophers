#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t *forks;
int n_global ;
void *hello(void *arg)
{
	int id = *(int *) arg;
	int left_fork = id;
	int right_fork = (id + 1) % n_global;

	printf("the philospher %d have the left fork %d and the right fork %d \n" , id , left_fork ,right_fork);

	printf("the philospher %d is thinking \n" , id);
	usleep(100000);

	printf("the philosopher %d is grabing his left fork %d \n" , id , left_fork);
	pthread_mutex_lock(&forks[left_fork]);

	printf("the philosopher %d is grabing his right fork %d \n" , id , right_fork);
	pthread_mutex_lock(&forks[right_fork]);

	printf("%d his now eating  \n" , id);
	usleep(500000);

	printf("%d his finish eating his meal \n", id);
	pthread_mutex_unlock(&forks[left_fork]);
	pthread_mutex_unlock(&forks[right_fork]);
	return NULL;
}
int main(int ac , char **av)
{
	int n = atoi(av[1]);
	n_global = n;
	forks = malloc(sizeof(pthread_mutex_t) * n);
	// if (!forks)
	// 	return NULL;

	for (int i = 0; i < n; i++)
		pthread_mutex_init(&forks[i] , NULL);
	
	pthread_t pthread_id[n] ;
	int thread_name[n];
	for (int i = 0; i < n; i++)
	{
		thread_name[i]  = i;
		pthread_create(&pthread_id[i] , NULL , hello , &thread_name[i]);
		printf("creating the threads\n");
	}
	
	printf("waiting ... \n");
	for (int i = 0; i < n; i++)
		pthread_join(pthread_id[i] , NULL);
	for (int i = 0; i < n; i++)
		pthread_mutex_destroy(&forks[i]);
	free(forks);
	printf("all died \n");	
}
