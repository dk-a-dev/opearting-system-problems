#include <stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
};

void findWaitingTime(struct Process processes[], int n, int waitingTime[]) {
    waitingTime[0] = 0;

    for (int i = 1; i < n; i++) {
        waitingTime[i] = processes[i-1].burstTime + waitingTime[i-1];
    }
}

void findCompletionTime(struct Process processes[], int n, int waitingTime[], int completionTime[]) {
    for (int i = 0; i < n; i++) {
        completionTime[i] = processes[i].arrivalTime + waitingTime[i] + processes[i].burstTime;
    }
}

void findTurnaroundTime(struct Process processes[], int n, int completionTime[], int turnaroundTime[]) {
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = completionTime[i] - processes[i].arrivalTime;
    }
}

void findAverageTime(struct Process processes[], int n) {
    int waitingTime[n], turnaroundTime[n], completionTime[n];
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    findWaitingTime(processes, n, waitingTime);
    findCompletionTime(processes, n, waitingTime, completionTime);
    findTurnaroundTime(processes, n, completionTime, turnaroundTime);
    printf("Processes  Arrival Time  Burst Time  Waiting Time  Turnaround Time  Completion Time\n");
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
        printf("   %d\t\t%d\t\t%d\t    %d\t\t    %d\t\t    %d\n", processes[i].pid, processes[i].arrivalTime, processes[i].burstTime, waitingTime[i], turnaroundTime[i], completionTime[i]);
    }

    printf("Average waiting time = %.2f\n", (float)totalWaitingTime / (float)n);
    printf("Average turnaround time = %.2f\n", (float)totalTurnaroundTime / (float)n);
}

int main() {
    struct Process processes[] = {{1, 0, 24}, {2, 1, 3}, {3, 2, 3}};
    int n = sizeof(processes) / sizeof(processes[0]);

    findAverageTime(processes, n);
    return 0;
}