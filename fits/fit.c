#include <stdio.h>
#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX_PROCESSES], i, j;
    int tempBlockSize[MAX_BLOCKS];
    
    for (i = 0; i < n; i++) {
        allocation[i] = -1;
    }
    for (i = 0; i < m; i++) {
        tempBlockSize[i] = blockSize[i];
    }
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (tempBlockSize[j] >= processSize[i]) {
                allocation[i] = j;
                tempBlockSize[j] -= processSize[i];
                break;
            }
        }
    }
    
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX_PROCESSES], i, j, bestIdx;
    int tempBlockSize[MAX_BLOCKS];
    
    for (i = 0; i < n; i++) {
        allocation[i] = -1;
    }
    for (i = 0; i < m; i++) {
        tempBlockSize[i] = blockSize[i];
    }
    
    for (i = 0; i < n; i++) {
        bestIdx = -1;
        for (j = 0; j < m; j++) {
            if (tempBlockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || tempBlockSize[j] < tempBlockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            tempBlockSize[bestIdx] -= processSize[i];
        }
    }
    
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX_PROCESSES], i, j, worstIdx;
    int tempBlockSize[MAX_BLOCKS];
    
    for (i = 0; i < n; i++) {
        allocation[i] = -1;
    }
    for (i = 0; i < m; i++) {
        tempBlockSize[i] = blockSize[i];
    }
    
    for (i = 0; i < n; i++) {
        worstIdx = -1;
        for (j = 0; j < m; j++) {
            if (tempBlockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || tempBlockSize[j] > tempBlockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            tempBlockSize[worstIdx] -= processSize[i];
        }
    }
    
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    int blockSize[MAX_BLOCKS], processSize[MAX_PROCESSES];
    int m, n, i;
    
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter size of each block:\n");
    for (i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter size of each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }
    
    printf("\nFirst Fit Allocation:\n");
    firstFit(blockSize, m, processSize, n);
    
    printf("\nBest Fit Allocation:\n");
    bestFit(blockSize, m, processSize, n);
    
    printf("\nWorst Fit Allocation:\n");
    worstFit(blockSize, m, processSize, n);
    
    return 0;
}

