#include <stdio.h>

typedef struct {
    char name[10];    // Process name
    int burstTime;    // Burst time of the process
    int priority;     // Priority of the process
    int waitTime;     // Waiting time of the process
    int turnAroundTime; // Turnaround time of the process
} Process;

void sortProcessesByPriority(Process processes[], int n) {
    // Sort processes by priority (ascending order)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].priority > processes[j].priority) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void calculateTimes(Process processes[], int n) {
    processes[0].waitTime = 0; // First process has no waiting time
    for (int i = 1; i < n; i++) {
        processes[i].waitTime = processes[i - 1].waitTime + processes[i - 1].burstTime;
    }
    for (int i = 0; i < n; i++) {
        processes[i].turnAroundTime = processes[i].waitTime + processes[i].burstTime;
    }
}

void printResults(Process processes[], int n) {
    printf("\nProcess\tPriority\tBurst Time\tWait Time\tTurnaround Time\n");
    int totalWait = 0, totalTurnAround = 0;
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].name, processes[i].priority, 
               processes[i].burstTime, processes[i].waitTime, processes[i].turnAroundTime);
        totalWait += processes[i].waitTime;
        totalTurnAround += processes[i].turnAroundTime;
    }
    printf("\nAverage Wait Time: %.2f\n", (float)totalWait / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnAround / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter process name, burst time, and priority for process %d: ", i + 1);
        scanf("%s %d %d", processes[i].name, &processes[i].burstTime, &processes[i].priority);
    }

    sortProcessesByPriority(processes, n);
    calculateTimes(processes, n);
    printResults(processes, n);

    return 0;
}
