#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int				shared_counter = 0;
pthread_mutex_t	counter_mutex = PTHREAD_MUTEX_INITIALIZER;
int				use_mutex = 1;

void	*counter_thread(void *arg)
{
	int	thread_id;

	thread_id = *(int *)arg;
	for (int i = 0; i < 100000; i++)
	{
		if (use_mutex)
			pthread_mutex_lock(&counter_mutex);
		shared_counter++;
		if (use_mutex)
			pthread_mutex_unlock(&counter_mutex);
	}
	printf("Thread %d finished\n", thread_id);
	return (NULL);
}

int	main(void)
{
	printf("=== DATA RACE DEMO (use_mutex = %d) ===\n", use_mutex);
	printf("Expected result: 200000\n");

	pthread_t threads[2];
	int ids[2] = {1, 2};

	for (int i = 0; i < 2; i++)
		pthread_create(&threads[i], NULL, counter_thread, &ids[i]);
	for (int i = 0; i < 2; i++)
		pthread_join(threads[i], NULL);

	printf("Actual result: %d\n", shared_counter);
	printf("Data race occurred: %s\n",
		(shared_counter != 200000) ? "YES" : "NO");

	return (0);
}