#include <stdio.h>
#include <stdbool.h>

void calculateNeed(int need[][10], int max[][10], int allocation[][10], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafe(int processes[], int available[], int max[][10], int allocation[][10], int n, int m) {
    int need[10][10];
    calculateNeed(need, max, allocation, n, m);

    bool finished[10] = {0};
    int safeSequence[10];
    int work[10];

    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finished[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count++] = i;
                    finished[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("The system is not in a safe state.\n");
            return false;
        }
    }

    printf("The system is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");
    return true;
}

int main() {
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int processes[10], allocation[10][10], max[10][10], available[10];

    for (int i = 0; i < n; i++) {
        processes[i] = i;
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the maximum matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the available resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    isSafe(processes, available, max, allocation, n, m);

    return 0;
}
