#include <stdio.h>

#define NUM_PROCESSES 5

typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int start_time;
    int end_time;
} Process;

void print_table(Process p[], int n) {
    printf("\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround\tCompletion\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t\t%d\n", p[i].id, p[i].arrival_time, p[i].burst_time,
               p[i].priority, p[i].waiting_time, p[i].turnaround_time, p[i].completion_time);
    }
}

void print_gantt_chart(Process p[], int n, int execution_order[]) {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        int idx = execution_order[i];
        printf("Process %d executed from %d to %d\n", p[idx].id, p[idx].start_time, p[idx].end_time);
    }
}

void sort_by_arrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival_time > p[j].arrival_time) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void sjf_non_preemptive(Process p[], int n, int execution_order[]) {
    int completed = 0, current_time = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;
    
    while (completed < n) {
        int idx = -1;
        int min_burst = 10000;
        
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].waiting_time == -1 && p[i].burst_time < min_burst) {
                min_burst = p[i].burst_time;
                idx = i;
            }
        }
        
        if (idx != -1) {
            p[idx].waiting_time = current_time - p[idx].arrival_time;
            p[idx].start_time = current_time;
            current_time += p[idx].burst_time;
            p[idx].end_time = current_time;
            p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            
            total_waiting_time += p[idx].waiting_time;
            total_turnaround_time += p[idx].turnaround_time;
            
            execution_order[completed] = idx;
            completed++;
        } else {
            current_time++;
        }
    }
    
    printf("\n--- SJF Scheduling ---\n");
    print_table(p, n);
    print_gantt_chart(p, n, execution_order);
    printf("Average Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

void priority_non_preemptive(Process p[], int n, int execution_order[]) {
    int completed = 0, current_time = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;
    
    while (completed < n) {
        int idx = -1;
        int min_priority = 10000;
        
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].waiting_time == -1 && p[i].priority < min_priority) {
                min_priority = p[i].priority;
                idx = i;
            }
        }
        
        if (idx != -1) {
            p[idx].waiting_time = current_time - p[idx].arrival_time;
            p[idx].start_time = current_time;
            current_time += p[idx].burst_time;
            p[idx].end_time = current_time;
            p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            
            total_waiting_time += p[idx].waiting_time;
            total_turnaround_time += p[idx].turnaround_time;
            
            execution_order[completed] = idx;
            completed++;
        } else {
            current_time++;
        }
    }
    
    printf("\n--- Priority Scheduling ---\n");
    print_table(p, n);
    print_gantt_chart(p, n, execution_order);
    printf("Average Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

int main() {
    Process processes_sjf[NUM_PROCESSES] = {
        {1, 0, 5, 2, -1, 0, 0, 0, 0},
        {2, 1, 3, 1, -1, 0, 0, 0, 0},
        {3, 2, 6, 3, -1, 0, 0, 0, 0},
        {4, 3, 1, 4, -1, 0, 0, 0, 0},
        {5, 4, 5, 2, -1, 0, 0, 0, 0}
    };

    Process processes_priority[NUM_PROCESSES];
    for (int i = 0; i < NUM_PROCESSES; i++) {
        processes_priority[i] = processes_sjf[i];
    }

    int execution_order_sjf[NUM_PROCESSES];
    int execution_order_priority[NUM_PROCESSES];

    // Sort processes by arrival time
    sort_by_arrival(processes_sjf, NUM_PROCESSES);
    sort_by_arrival(processes_priority, NUM_PROCESSES);

    // Calculate for SJF
    sjf_non_preemptive(processes_sjf, NUM_PROCESSES, execution_order_sjf);

    // Reset waiting, turnaround, and completion times for Priority Scheduling
    for (int i = 0; i < NUM_PROCESSES; i++) {
        processes_priority[i].waiting_time = -1;
        processes_priority[i].turnaround_time = 0;
        processes_priority[i].completion_time = 0;
        processes_priority[i].start_time = 0;
        processes_priority[i].end_time = 0;
    }

    // Calculate for Priority Scheduling
    priority_non_preemptive(processes_priority, NUM_PROCESSES, execution_order_priority);

    return 0;
}