#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *hello (void *arg)
{
	char *name  = arg;
	printf("hello my name %s" , name);
	sleep(2);
	return NULL;
}
int main()
{
	pthread_t thread_id;
	char *thread_name = "ayoub";

	pthread_create(&thread_id , NULL, hello, thread_name);
	printf("created");
}