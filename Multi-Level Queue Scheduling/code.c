#include <stdio.h>

typedef struct {
    char name[10];
    int burstTime;
    int waitTime;
    int turnAroundTime;
    int priority;
} Process;

void calculateTimes(Process processes[], int n) {
    processes[0].waitTime = 0;
    for (int i = 1; i < n; i++) {
        processes[i].waitTime = processes[i - 1].waitTime + processes[i - 1].burstTime;
    }
    for (int i = 0; i < n; i++) {
        processes[i].turnAroundTime = processes[i].waitTime + processes[i].burstTime;
    }
}

void printResults(Process processes[], int n) {
    printf("\nProcess\tBurst Time\tWait Time\tTurnaround Time\n");
    int totalWait = 0, totalTurnAround = 0;
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t\t%d\t\t%d\n", processes[i].name, processes[i].burstTime,
               processes[i].waitTime, processes[i].turnAroundTime);
        totalWait += processes[i].waitTime;
        totalTurnAround += processes[i].turnAroundTime;
    }
    printf("\nAverage Wait Time: %.2f\n", (float)totalWait / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnAround / n);
}

int main() {
    int n1, n2;

    printf("Enter the number of system processes: ");
    scanf("%d", &n1);
    Process systemProcesses[n1];
    printf("Enter process name and burst time for system processes:\n");
    for (int i = 0; i < n1; i++) {
        scanf("%s %d", systemProcesses[i].name, &systemProcesses[i].burstTime);
    }

    printf("Enter the number of user processes: ");
    scanf("%d", &n2);
    Process userProcesses[n2];
    printf("Enter process name and burst time for user processes:\n");
    for (int i = 0; i < n2; i++) {
        scanf("%s %d", userProcesses[i].name, &userProcesses[i].burstTime);
    }

    printf("\nScheduling System Processes (Higher Priority):\n");
    calculateTimes(systemProcesses, n1);
    printResults(systemProcesses, n1);

    printf("\nScheduling User Processes (Lower Priority):\n");
    calculateTimes(userProcesses, n2);
    printResults(userProcesses, n2);

    return 0;
}
