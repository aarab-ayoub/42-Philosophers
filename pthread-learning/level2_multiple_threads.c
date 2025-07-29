#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *hello (void *arg)
{
    int name = *(int *)arg;
    printf("Thread started: hello my name %d\n", name);
    usleep(500000);
    printf("Thread ending %d \n", name);
    return NULL;
}

int main()
{
    int size = 4;
    pthread_t thread_id[size];
    int thread_id_name[size];

    for (int i = 0; i < size; i++)
    {
        thread_id_name[i] = i; 
        printf("Creating thread...\n");
        pthread_create(&thread_id[i], NULL, hello, &thread_id_name[i]);
        // printf("Thread created, now waiting...\n");
    }
    printf("All threads created, now waiting...\n");

    for (int i = 0; i < size; i++)
    {
        pthread_join(thread_id[i], NULL);
        printf("Thread finished, main exiting\n");
    }
    printf("All threads finished, main exiting\n");
    return 0;
}