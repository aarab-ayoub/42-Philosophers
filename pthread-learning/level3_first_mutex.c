/*
 * LEVEL 3: Your First Mutex
 * Goal: See why mutexes are needed and how they work
 */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Shared variable (dangerous without protection!)
int shared_counter = 0;

// Our first mutex
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *counter_worker(void *arg) {
    int worker_id = *(int *)arg;
    
    for (int i = 0; i < 5; i++) {
        // CRITICAL SECTION - only one thread at a time
        pthread_mutex_lock(&counter_mutex);
        printf("🔒 Worker %d: Got the lock! Counter is %d\n", worker_id, shared_counter);
        
        int old_value = shared_counter;
        usleep(100000); // 100ms delay - simulate some work
        shared_counter = old_value + 1;
        
        printf("🔒 Worker %d: Updated counter from %d to %d\n", worker_id, old_value, shared_counter);
        pthread_mutex_unlock(&counter_mutex);
        printf("🔓 Worker %d: Released the lock\n", worker_id);
        
        // Do some other work outside critical section
        usleep(50000); // 50ms
    }
    
    return NULL;
}

int main() {
    printf("=== LEVEL 3: Your First Mutex ===\n");
    printf("🏠 Starting with counter = %d\n", shared_counter);
    
    const int num_workers = 2;
    pthread_t threads[num_workers];
    int worker_ids[num_workers];
    
    // Create workers
    for (int i = 0; i < num_workers; i++) {
        worker_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, counter_worker, &worker_ids[i]);
    }
    
    // Wait for workers
    for (int i = 0; i < num_workers; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("🏠 Final counter value: %d\n", shared_counter);
    printf("🏠 Expected: 10 (2 workers × 5 increments each)\n");
    
    pthread_mutex_destroy(&counter_mutex);
    return 0;
}

/*
 * COMPILE: gcc level3.c -pthread -o level3
 * RUN: ./level3
 * 
 * WHAT TO OBSERVE:
 * - Only one worker can update the counter at a time
 * - Workers wait for each other (you'll see the lock/unlock messages)
 * - Final result is always correct (10)
 * - Try commenting out the mutex lock/unlock to see chaos!
 */
