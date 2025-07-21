#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *hello (void *arg)
{
    char *name = arg;
    printf("Thread started: hello my name %s\n", name);
    sleep(3);
    printf("Thread ending\n");
    return NULL;
}

int main()
{
    pthread_t thread_id;
    char *thread_name = "ayoub";

    printf("Creating thread...\n");
    pthread_create(&thread_id, NULL, hello, thread_name);
    printf("Thread created, now waiting...\n");
    
    pthread_join(thread_id, NULL);
    printf("Thread finished, main exiting\n");
    
    return 0;
}