#include <stdio.h>
#include <stdbool.h>

#define NUM_PROCESSES 5
#define NUM_RESOURCES 4

void displayMatrix(int matrix[NUM_PROCESSES][NUM_RESOURCES], const char *name) {
    printf("Matrix %s:\n", name);
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

bool isSafe(int allocation[NUM_PROCESSES][NUM_RESOURCES], int max[NUM_PROCESSES][NUM_RESOURCES], int available[NUM_RESOURCES], int need[NUM_PROCESSES][NUM_RESOURCES], int finishOrder[NUM_PROCESSES]) {
    int work[NUM_RESOURCES];
    bool finish[NUM_PROCESSES] = {false};

    for (int i = 0; i < NUM_RESOURCES; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < NUM_PROCESSES) {
        bool found = false;
        for (int p = 0; p < NUM_PROCESSES; p++) {
            if (!finish[p]) {
                bool canAllocate = true;
                for (int r = 0; r < NUM_RESOURCES; r++) {
                    if (need[p][r] > work[r]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int r = 0; r < NUM_RESOURCES; r++) {
                        work[r] += allocation[p][r];
                    }
                    finishOrder[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

bool requestResources(int process, int request[NUM_RESOURCES], int allocation[NUM_PROCESSES][NUM_RESOURCES], int need[NUM_PROCESSES][NUM_RESOURCES], int available[NUM_RESOURCES], int max[NUM_PROCESSES][NUM_RESOURCES]) {
    for (int r = 0; r < NUM_RESOURCES; r++) {
        if (request[r] > need[process][r]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
    }

    for (int r = 0; r < NUM_RESOURCES; r++) {
        if (request[r] > available[r]) {
            printf("Error: Resources are not available.\n");
            return false;
        }
    }

    for (int r = 0; r < NUM_RESOURCES; r++) {
        available[r] -= request[r];
        allocation[process][r] += request[r];
        need[process][r] -= request[r];
    }

    int finishOrder[NUM_PROCESSES];
    if (isSafe(allocation, max, available, need, finishOrder)) {
        printf("Request can be granted. System remains in a safe state.\n");
        return true;
    } else {
        for (int r = 0; r < NUM_RESOURCES; r++) {
            available[r] += request[r];
            allocation[process][r] -= request[r];
            need[process][r] += request[r];
        }
        printf("Request cannot be granted. System would be in an unsafe state.\n");
        return false;
    }
}

int main() {
    int allocation[NUM_PROCESSES][NUM_RESOURCES] = {
        {0, 1, 0, 3},
        {1, 0, 0, 1},
        {1, 3, 2, 0},
        {1, 2, 1, 2},
        {0, 0, 1, 1}
    };

    int max[NUM_PROCESSES][NUM_RESOURCES] = {
        {0, 1, 0, 3},
        {2, 2, 2, 2},
        {3, 3, 2, 1},
        {1, 2, 2, 2},
        {2, 1, 1, 2}
    };

    int available[NUM_RESOURCES] = {2, 3, 1, 2};

    int need[NUM_PROCESSES][NUM_RESOURCES];
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    printf("Initial Need Matrix:\n");
    displayMatrix(need, "Need");

    int finishOrder[NUM_PROCESSES];
    if (isSafe(allocation, max, available, need, finishOrder)) {
        printf("System is in a safe state.\n");
        printf("Safe sequence: ");
        for (int i = 0; i < NUM_PROCESSES; i++) {
            printf("P%d ", finishOrder[i]);
        }
        printf("\n");
    } else {
        printf("System is in an unsafe state.\n");
    }

    int request[NUM_RESOURCES] = {1, 0, 1, 0};
    if (requestResources(1, request, allocation, need, available, max)) {
        printf("Request granted.\n");
    } else {
        printf("Request denied.\n");
    }

    printf("Need Matrix after request:\n");
    displayMatrix(need, "Need");

    return 0;
}