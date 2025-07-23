#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t fork1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fork2 = PTHREAD_MUTEX_INITIALIZER;
int prevent_deadlock = 0; // Toggle: 0 = deadlock, 1 = safe

void *philosopher1(void *arg) {
    printf("Philosopher 1: Starting\n");
    
    if (prevent_deadlock) {
        // SAFE: Always grab fork1 first, then fork2
        pthread_mutex_lock(&fork1);
        printf("Philosopher 1: Got fork1\n");
        usleep(100000); // Wait a bit
        pthread_mutex_lock(&fork2);
        printf("Philosopher 1: Got fork2 - EATING!\n");
    } else {
        // DANGEROUS: Grab fork1 first, then fork2
        pthread_mutex_lock(&fork1);
        printf("Philosopher 1: Got fork1\n");
        usleep(100000); // Wait a bit - gives time for deadlock
        pthread_mutex_lock(&fork2);
        printf("Philosopher 1: Got fork2 - EATING!\n");
    }
    
    usleep(200000); // Eat
    pthread_mutex_unlock(&fork2);
    pthread_mutex_unlock(&fork1);
    printf("Philosopher 1: Finished eating\n");
    
    return NULL;
}

void *philosopher2(void *arg) {
    printf("Philosopher 2: Starting\n");
    
    if (prevent_deadlock) {
        // SAFE: Always grab fork1 first, then fork2 (same order!)
        pthread_mutex_lock(&fork1);
        printf("Philosopher 2: Got fork1\n");
        usleep(100000);
        pthread_mutex_lock(&fork2);
        printf("Philosopher 2: Got fork2 - EATING!\n");
    } else {
        // DANGEROUS: Grab fork2 first, then fork1 (opposite order!)
        pthread_mutex_lock(&fork2);
        printf("Philosopher 2: Got fork2\n");
        usleep(100000); // Wait a bit - creates deadlock!
        pthread_mutex_lock(&fork1);
        printf("Philosopher 2: Got fork1 - EATING!\n");
    }
    
    usleep(200000); // Eat
    pthread_mutex_unlock(&fork1);
    pthread_mutex_unlock(&fork2);
    printf("Philosopher 2: Finished eating\n");
    
    return NULL;
}

int main() {
    printf("=== DEADLOCK DEMO (prevent_deadlock = %d) ===\n", prevent_deadlock);
    
    pthread_t phil1, phil2;
    
    pthread_create(&phil1, NULL, philosopher1, NULL);
    pthread_create(&phil2, NULL, philosopher2, NULL);
    
    printf("If program hangs here, we have DEADLOCK!\n");
    
    pthread_join(phil1, NULL);
    pthread_join(phil2, NULL);
    
    printf("Both philosophers finished successfully!\n");
    return 0;
}