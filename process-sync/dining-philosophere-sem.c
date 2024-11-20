#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
 
void dine(int n);
pthread_t *philosopher;
pthread_mutex_t *chopstick;
int num_philosophers;
int num_chopsticks;
 
int main() {
   int i, status_message;
   void *msg;
   printf("Enter the number of philosophers: ");
   scanf("%d", &num_philosophers);
   printf("Enter the number of chopsticks (at least %d): ", num_philosophers);
   scanf("%d", &num_chopsticks);
   if (num_chopsticks < num_philosophers) {
       printf("Number of chopsticks must be at least equal to the number of philosophers.\n");
       exit(1);
   }
   philosopher = (pthread_t *)malloc(num_philosophers * sizeof(pthread_t));
   chopstick = (pthread_mutex_t *)malloc(num_chopsticks * sizeof(pthread_mutex_t));
   for (i = 0; i < num_chopsticks; i++) {
       status_message = pthread_mutex_init(&chopstick[i], NULL);
       if (status_message != 0) {
           printf("\n Mutex initialization failed");
           exit(1);
       }
   }
   for (i = 0; i < num_philosophers; i++) {
       status_message = pthread_create(&philosopher[i], NULL, (void *)dine, (void *)(long)i);
       if (status_message != 0) {
           printf("\n Thread creation error \n");
           exit(1);
       }
   }
   for (i = 0; i < num_philosophers; i++) {
       status_message = pthread_join(philosopher[i], &msg);
       if (status_message != 0) {
           printf("\n Thread join failed \n");
           exit(1);
       }
   }
   for (i = 0; i < num_chopsticks; i++) {
       status_message = pthread_mutex_destroy(&chopstick[i]);
       if (status_message != 0) {
           printf("\n Mutex Destroyed \n");
           exit(1);
       }
   }
   free(philosopher);
   free(chopstick);
   return 0;
}
 
void dine(int n) {
   printf("Philosopher %d is thinking \n", n);
   pthread_mutex_lock(&chopstick[n]);
   pthread_mutex_lock(&chopstick[(n + 1) % num_chopsticks]);
   printf("\nPhilosopher %d is eating \n", n);
   sleep(3);
   pthread_mutex_unlock(&chopstick[n]);
   pthread_mutex_unlock(&chopstick[(n + 1) % num_chopsticks]);
   printf("\nPhilosopher %d Finished eating \n", n);
}