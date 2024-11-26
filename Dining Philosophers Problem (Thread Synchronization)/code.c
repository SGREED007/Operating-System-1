#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (philosopherNumber + 4) % N
#define RIGHT (philosopherNumber + 1) % N

sem_t mutex;
sem_t S[N];
int state[N];

void test(int philosopherNumber) {
    if (state[philosopherNumber] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[philosopherNumber] = EATING;
        printf("Philosopher %d is Eating\n", philosopherNumber + 1);
        sem_post(&S[philosopherNumber]);
    }
}

void pickUpForks(int philosopherNumber) {
    sem_wait(&mutex);
    state[philosopherNumber] = HUNGRY;
    printf("Philosopher %d is Hungry\n", philosopherNumber + 1);
    test(philosopherNumber);
    sem_post(&mutex);
    sem_wait(&S[philosopherNumber]);
}

void putDownForks(int philosopherNumber) {
    sem_wait(&mutex);
    state[philosopherNumber] = THINKING;
    printf("Philosopher %d is Thinking\n", philosopherNumber + 1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void *philosopher(void *num) {
    int philosopherNumber = *(int *)num;
    while (1) {
        printf("Philosopher %d is Thinking\n", philosopherNumber + 1);
        sleep(1);
        pickUpForks(philosopherNumber);
        sleep(1);
        putDownForks(philosopherNumber);
    }
}

int main() {
    pthread_t threadId[N];
    int philosopherNumbers[N];

    sem_init(&mutex, 0, 1);
    for (int i = 0; i < N; i++) {
        sem_init(&S[i], 0, 0);
    }

    for (int i = 0; i < N; i++) {
        philosopherNumbers[i] = i;
        pthread_create(&threadId[i], NULL, philosopher, &philosopherNumbers[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threadId[i], NULL);
    }

    return 0;
}
