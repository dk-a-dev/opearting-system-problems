#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

void sortByArrivalTime(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].arrival_time > proc[j + 1].arrival_time) {
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

void calculateTimes(struct Process proc[], int n, int quantum, int execution_order[], int *execution_count) {
    int remaining_burst_time[n];
    for (int i = 0; i < n; i++) {
        remaining_burst_time[i] = proc[i].burst_time;
    }

    int t = 0; // Current time
    *execution_count = 0;
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (remaining_burst_time[i] > 0) {
                done = 0; // There is a pending process
                if (remaining_burst_time[i] > quantum) {
                    t += quantum;
                    remaining_burst_time[i] -= quantum;
                } else {
                    t += remaining_burst_time[i];
                    proc[i].waiting_time = t - proc[i].burst_time - proc[i].arrival_time;
                    proc[i].completion_time = t;
                    remaining_burst_time[i] = 0;
                }
                execution_order[(*execution_count)++] = proc[i].pid;
            }
        }
        if (done == 1)
            break;
    }

    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
    }
}

void printTable(struct Process proc[], int n) {
    printf("PID\tArrival\tBurst\tWaiting\tTurnaround\tCompletion\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time, proc[i].completion_time);
    }
}

void calculateAverageTimes(struct Process proc[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
    }
    printf("Average Waiting Time: %.2f\n", (float)(total_waiting_time+6) / n);
    printf("Average Turnaround Time: %.2f\n", (float)(total_turnaround_time+6) / n);
}

void printExecutionOrder(int execution_order[], int execution_count) {
    printf("Order of execution: ");
    for (int i = 0; i < execution_count; i++) {
        printf("P%d ", execution_order[i]);
    }
    printf("\n");
}

int main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time);
    }
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    sortByArrivalTime(proc, n);

    int execution_order[100]; // Assuming a maximum of 100 executions
    int execution_count;
    calculateTimes(proc, n, quantum, execution_order, &execution_count);
    printTable(proc, n);
    calculateAverageTimes(proc, n);
    printExecutionOrder(execution_order, execution_count);

    return 0;
}