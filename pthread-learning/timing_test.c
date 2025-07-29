/*
 * Timing Precision Test
 * Goal: See the difference between sleep() and precise timing
 */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

// Get current time in milliseconds
size_t get_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void *imprecise_worker(void *arg) {
    printf("🧵 Starting imprecise sleep...\n");
    
    size_t start = get_time_ms();
    sleep(2); // "About 2 seconds"
    size_t end = get_time_ms();
    
    printf("🧵 Imprecise: Asked for 2000ms, actually slept %zu ms\n", end - start);
    return NULL;
}

void *precise_worker(void *arg) {
    printf("🧵 Starting precise sleep...\n");
    
    size_t start = get_time_ms();
    usleep(2000000); // Exactly 2,000,000 microseconds
    size_t end = get_time_ms();
    
    printf("🧵 Precise: Asked for 2000ms, actually slept %zu ms\n", end - start);
    return NULL;
}

void *measured_worker(void *arg) {
    printf("🧵 Starting measured work...\n");
    
    size_t start = get_time_ms();
    size_t target_time = start + 2000; // Exactly 2000ms from now
    
    // Busy wait until exact time (not recommended for real apps!)
    while (get_time_ms() < target_time) {
        usleep(1000); // Check every 1ms
    }
    
    size_t end = get_time_ms();
    printf("🧵 Measured: Targeted 2000ms, actually took %zu ms\n", end - start);
    return NULL;
}

int main() {
    printf("=== TIMING PRECISION TEST ===\n");
    
    pthread_t threads[3];
    
    // Test different timing methods
    pthread_create(&threads[0], NULL, imprecise_worker, NULL);
    pthread_create(&threads[1], NULL, precise_worker, NULL);
    pthread_create(&threads[2], NULL, measured_worker, NULL);
    
    // Wait for all
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("🏠 Notice the timing differences!\n");
    return 0;
}

/*
 * COMPILE: gcc timing_test.c -pthread -o timing_test
 * RUN: ./timing_test
 */
