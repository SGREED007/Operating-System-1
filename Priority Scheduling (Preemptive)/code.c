#include <stdio.h>

typedef struct {
    char name[10];
    int burstTime;
    int priority;
    int remainingTime;
    int waitTime;
    int turnAroundTime;
    int completed;
} Process;

void priorityScheduling(Process processes[], int n) {
    int time = 0, completed = 0;

    while (completed < n) {
        int highestPriority = -1, index = -1;

        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && (index == -1 || processes[i].priority < highestPriority)) {
                highestPriority = processes[i].priority;
                index = i;
            }
        }

        if (index != -1) {
            processes[index].remainingTime -= 1;
            time++;

            if (processes[index].remainingTime == 0) {
                processes[index].completed = 1;
                processes[index].turnAroundTime = time;
                processes[index].waitTime = processes[index].turnAroundTime - processes[index].burstTime;
                completed++;
            }
        }
    }
}

void printPriorityResults(Process processes[], int n) {
    printf("\nProcess\tBurst Time\tPriority\tWait Time\tTurnaround Time\n");
    int totalWait = 0, totalTurnAround = 0;
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].name, processes[i].burstTime,
               processes[i].priority, processes[i].waitTime, processes[i].turnAroundTime);
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
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].completed = 0;
    }

    priorityScheduling(processes, n);
    printPriorityResults(processes, n);

    return 0;
}
