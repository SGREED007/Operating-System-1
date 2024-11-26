#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void cscan(int requests[], int n, int start, int diskSize) {
    int seekTime = 0, current = start;

    sort(requests, n);

    printf("C-SCAN Seek Sequence: %d -> ", start);

    // Move towards the end of the disk
    for (int i = 0; i < n; i++) {
        if (requests[i] >= start) {
            seekTime += abs(current - requests[i]);
            current = requests[i];
            printf("%d -> ", requests[i]);
        }
    }

    // Jump to the start of the disk
    seekTime += abs(current - (diskSize - 1));
    seekTime += diskSize - 1;
    current = 0;

    // Move from the start to the remaining requests
    for (int i = 0; i < n; i++) {
        if (requests[i] < start) {
            seekTime += abs(current - requests[i]);
            current = requests[i];
            printf("%d -> ", requests[i]);
        }
    }

    printf("End\nTotal Seek Time: %d\n", seekTime);
}

int main() {
    int n, start, diskSize;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    int requests[n];

    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the starting head position: ");
    scanf("%d", &start);

    printf("Enter the disk size: ");
    scanf("%d", &diskSize);

    cscan(requests, n, start, diskSize);

    return 0;
}
