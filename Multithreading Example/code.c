#include <pthread.h>
#include <stdio.h>

#define MAX 1000
#define THREAD_COUNT 2

int arr[MAX];
int sum[THREAD_COUNT] = {0};
int part = 0;

void *sumArray(void *arg) {
    int threadPart = part++;
    int start = threadPart * (MAX / THREAD_COUNT);
    int end = (threadPart + 1) * (MAX / THREAD_COUNT);

    for (int i = start; i < end; i++) {
        sum[threadPart] += arr[i];
    }

    return NULL;
}

int main() {
    pthread_t threads[THREAD_COUNT];

    // Initialize the array
    for (int i = 0; i < MAX; i++) {
        arr[i] = i + 1; // 1 to MAX
    }

    // Create threads
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, sumArray, NULL);
    }

    // Wait for threads to finish
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    // Calculate total sum
    int totalSum = 0;
    for (int i = 0; i < THREAD_COUNT; i++) {
        totalSum += sum[i];
    }

    printf("Sum of array: %d\n", totalSum);

    return 0;
}
