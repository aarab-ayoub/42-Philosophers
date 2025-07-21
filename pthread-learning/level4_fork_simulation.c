/*
 * LEVEL 4: Fork Simulation - Philosophy Prep!
 * Goal: Understand how philosophers will grab forks
 */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Simulate 3 forks on a table
pthread_mutex_t forks[3];

// Person trying to eat (like a philosopher)
void *person(void *arg) {
    int person_id = *(int *)arg;
    int left_fork = person_id;
    int right_fork = (person_id + 1) % 3; // Circular table
    
    printf("🧑 Person %d sits between fork %d (left) and fork %d (right)\n", 
           person_id, left_fork, right_fork);
    
    // Try to eat 3 times
    for (int meal = 1; meal <= 3; meal++) {
        printf("🤔 Person %d is hungry (meal %d)\n", person_id, meal);
        
        // Try to grab forks
        printf("👈 Person %d reaching for LEFT fork %d...\n", person_id, left_fork);
        pthread_mutex_lock(&forks[left_fork]);
        printf("✅ Person %d got LEFT fork %d!\n", person_id, left_fork);
        
        printf("👉 Person %d reaching for RIGHT fork %d...\n", person_id, right_fork);
        pthread_mutex_lock(&forks[right_fork]);
        printf("✅ Person %d got RIGHT fork %d!\n", person_id, right_fork);
        
        // Eating
        printf("🍝 Person %d is EATING (meal %d)!\n", person_id, meal);
        usleep(500000); // Eat for 500ms
        
        // Put down forks
        printf("🔽 Person %d putting down RIGHT fork %d\n", person_id, right_fork);
        pthread_mutex_unlock(&forks[right_fork]);
        
        printf("🔽 Person %d putting down LEFT fork %d\n", person_id, left_fork);
        pthread_mutex_unlock(&forks[left_fork]);
        
        printf("😴 Person %d is resting...\n", person_id);
        usleep(300000); // Rest for 300ms
    }
    
    printf("🎉 Person %d finished all meals!\n", person_id);
    return NULL;
}

int main() {
    printf("=== LEVEL 4: Fork Simulation ===\n");
    printf("🍴 Setting up 3 forks on the table...\n");
    
    // Initialize fork mutexes
    for (int i = 0; i < 3; i++) {
        pthread_mutex_init(&forks[i], NULL);
        printf("Fork %d ready\n", i);
    }
    
    const int num_people = 3;
    pthread_t people[num_people];
    int person_ids[num_people];
    
    // Create people
    printf("\n👥 %d people sit around the table...\n", num_people);
    for (int i = 0; i < num_people; i++) {
        person_ids[i] = i;
        pthread_create(&people[i], NULL, person, &person_ids[i]);
    }
    
    // Wait for everyone to finish
    for (int i = 0; i < num_people; i++) {
        pthread_join(people[i], NULL);
    }
    
    printf("\n🎊 Dinner is over!\n");
    
    // Clean up
    for (int i = 0; i < 3; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    
    return 0;
}

/*
 * COMPILE: gcc level4.c -pthread -o level4
 * RUN: ./level4
 * 
 * WHAT TO OBSERVE:
 * - People wait for forks to be available
 * - This might deadlock sometimes! (All grab left fork, wait for right)
 * - This is EXACTLY the dining philosophers problem!
 * 
 * TRY RUNNING IT MULTIPLE TIMES - you might see deadlock!
 */
