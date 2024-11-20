#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h> 

pthread_t *producers;
pthread_t *consumers;

sem_t *buf_mutex, *empty_count, *fill_count;

int *buf, buf_pos = -1, prod_count, con_count, buf_len;

int produce(pthread_t self) {
    int i = 0;
    return rand() % 100;
}

void consume(int item, pthread_t self) {
    printf("Consumer %ld consumed item %d\n", self, item);
}

void* producer(void* arg) {
    pthread_t self = pthread_self();
    while (1) {
        int item = produce(self);
        sem_wait(empty_count);
        sem_wait(buf_mutex);

        buf[++buf_pos] = item;
        printf("Producer %ld produced item %d\n", self, item);

        sem_post(buf_mutex);
        sem_post(fill_count);

        sleep(rand() % 3);
    }
}

void* consumer(void* arg) {
    pthread_t self = pthread_self();
    while (1) {
        sem_wait(fill_count);
        sem_wait(buf_mutex);

        int item = buf[buf_pos--];
        consume(item, self);

        sem_post(buf_mutex);
        sem_post(empty_count);

        sleep(rand() % 3);
    }
}

int main() {
    srand(time(NULL));

    printf("Enter the number of producers: ");
    scanf("%d", &prod_count);
    printf("Enter the number of consumers: ");
    scanf("%d", &con_count);
    printf("Enter the buffer length: ");
    scanf("%d", &buf_len);

    buf = (int*)malloc(buf_len * sizeof(int));
    producers = (pthread_t*)malloc(prod_count * sizeof(pthread_t));
    consumers = (pthread_t*)malloc(con_count * sizeof(pthread_t));

    buf_mutex = sem_open("/buf_mutex", O_CREAT, 0644, 1);
    fill_count = sem_open("/fill_count", O_CREAT, 0644, 0);
    empty_count = sem_open("/empty_count", O_CREAT, 0644, buf_len);

    for (int i = 0; i < prod_count; i++) {
        pthread_create(&producers[i], NULL, producer, NULL);
    }
    for (int i = 0; i < con_count; i++) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }

    for (int i = 0; i < prod_count; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < con_count; i++) {
        pthread_join(consumers[i], NULL);
    }

    sem_close(buf_mutex);
    sem_close(fill_count);
    sem_close(empty_count);
    sem_unlink("/buf_mutex");
    sem_unlink("/fill_count");
    sem_unlink("/empty_count");

    free(buf);
    free(producers);
    free(consumers);

    return 0;
}