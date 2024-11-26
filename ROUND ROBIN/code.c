#include <stdio.h>

typedef struct {
    char name[10]; // Process name
    int burstTime; // Burst time of the process
    int remainingTime; // Remaining time for the process
    int waitTime; // Waiting time for the process
    int turnAroundTime; // Turnaround time for the process
} Process;

void calculateTimes(Process processes[], int n, int timeQuantum) {
    int time = 0; // Current time
    int completed = 0; // Number of completed processes

    // Initialize remaining time for each process
    for (int i = 0; i < n; i++) {
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].waitTime = 0;
    }

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0) {
                if (processes[i].remainingTime > timeQuantum) {
                    time += timeQuantum;
                    processes[i].remainingTime -= timeQuantum;
                } else {
                    time += processes[i].remainingTime;
                    processes[i].remainingTime = 0;
                    processes[i].turnAroundTime = time;
                    processes[i].waitTime = processes[i].turnAroundTime - processes[i].burstTime;
                    completed++;
                }
            }
        }
    }
}

void printResults(Process processes[], int n) {
    printf("\nProcess\tBurst Time\tWait Time\tTurnaround Time\n");
    int totalWait = 0, totalTurnAround = 0;
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t\t%d\t\t%d\n", processes[i].name, processes[i].burstTime, processes[i].waitTime, processes[i].turnAroundTime);
        totalWait += processes[i].waitTime;
        totalTurnAround += processes[i].turnAroundTime;
    }
    printf("\nAverage Wait Time: %.2f\n", (float)totalWait / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnAround / n);
}

int main() {
    int n, timeQuantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter process name, burst time for process %d: ", i + 1);
        scanf("%s %d", processes[i].name, &processes[i].burstTime);
    }

    printf("Enter the time quantum: ");
    scanf("%d", &timeQuantum);

    calculateTimes(processes, n, timeQuantum);
    printResults(processes, n);

    return 0;
}
