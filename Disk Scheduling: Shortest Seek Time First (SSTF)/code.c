#include <stdio.h>
#include <stdlib.h>

void sort(int requests[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

int findClosest(int requests[], int n, int current) {
    int minDistance = abs(requests[0] - current);
    int index = 0;

    for (int i = 1; i < n; i++) {
        int distance = abs(requests[i] - current);
        if (distance < minDistance) {
            minDistance = distance;
            index = i;
        }
    }

    return index;
}

void sstf(int requests[], int n, int start) {
    int totalSeek = 0, current = start;
    printf("\nSeek Sequence: %d ", start);

    for (int i = 0; i < n; i++) {
        int closestIndex = findClosest(requests, n, current);
        totalSeek += abs(requests[closestIndex] - current);
        current = requests[closestIndex];
        printf("-> %d ", current);

        // Remove serviced request
        for (int j = closestIndex; j < n - 1; j++) {
            requests[j] = requests[j + 1];
        }
        n--;
    }

    printf("\nTotal Seek Time: %d\n", totalSeek);
}

int main() {
    int n, start;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the starting head position: ");
    scanf("%d", &start);

    sstf(requests, n, start);

    return 0;
}
