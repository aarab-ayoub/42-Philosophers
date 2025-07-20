/*
 * LEVEL 2: Multiple Threads
 * Goal: Create several threads working simultaneously
 */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Each thread gets a number
void *worker(void *arg) {
    int worker_id = *(int *)arg;
    
    printf("🧵 Worker %d starting work\n", worker_id);
    
    // Each worker does different amount of work
    sleep(worker_id); // Worker 1 sleeps 1s, Worker 2 sleeps 2s, etc.
    
    printf("🧵 Worker %d finished!\n", worker_id);
    
    return NULL;
}

int main() {
    printf("=== LEVEL 2: Multiple Threads ===\n");
    
    const int num_workers = 3;
    pthread_t threads[num_workers];
    int worker_ids[num_workers];
    
    // Create multiple threads
    printf("🏠 Creating %d workers...\n", num_workers);
    for (int i = 0; i < num_workers; i++) {
        worker_ids[i] = i + 1; // Worker IDs: 1, 2, 3
        pthread_create(&threads[i], NULL, worker, &worker_ids[i]);
        printf("🏠 Created worker %d\n", worker_ids[i]);
    }
    
    printf("🏠 All workers created! Waiting for them to finish...\n");
    
    // Wait for all threads to finish
    for (int i = 0; i < num_workers; i++) {
        pthread_join(threads[i], NULL);
        printf("🏠 Worker %d has returned\n", worker_ids[i]);
    }
    
    printf("🏠 All workers done!\n");
    return 0;
}

/*
 * COMPILE: gcc level2.c -pthread -o level2
 * RUN: ./level2
 * 
 * WHAT TO OBSERVE:
 * - All threads start almost simultaneously
 * - They finish in different order (Worker 1 finishes first)
 * - pthread_join() waits for each one individually
 */
