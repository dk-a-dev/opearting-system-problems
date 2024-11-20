#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int predict(int pages[], int frame[], int n, int frame_size, int index)
{
    int res = -1, farthest = index;
    for (int i = 0; i < frame_size; i++)
    {
        int j;
        for (j = index; j < n; j++)
        {
            if (frame[i] == pages[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}

int optimalPageReplacement(int pages[], int n, int capacity)
{
    int *frame = (int *)malloc(capacity * sizeof(int));
    int frame_size = 0;
    int page_faults = 0;
    for (int i = 0; i < n; i++)
    {
        int found = 0;
        for (int j = 0; j < frame_size; j++)
        {
            if (frame[j] == pages[i])
            {
                found = 1;
                break;
            }
        }
        if (found)
            continue;
        if (frame_size < capacity)
            frame[frame_size++] = pages[i];
        else
        {
            int j = predict(pages, frame, n, frame_size, i + 1);
            frame[j] = pages[i];
        }
        page_faults++;
    }
    free(frame);
    return page_faults;
}
int lruPageReplacement(int pages[], int n, int capacity)
{
    int *frame = (int *)malloc(capacity * sizeof(int));
    int *indexes = (int *)malloc(capacity * sizeof(int));
    int page_faults = 0;
    int frame_size = 0;

    for (int i = 0; i < n; i++)
    {
        int found = 0;
        for (int j = 0; j < frame_size; j++)
        {
            if (frame[j] == pages[i])
            {
                found = 1;
                indexes[j] = i;
                break;
            }
        }
        if (!found)
        {
            if (frame_size < capacity)
            {
                frame[frame_size] = pages[i];
                indexes[frame_size] = i;
                frame_size++;
            }
            else
            {
                int lru = 0;
                for (int j = 1; j < frame_size; j++)
                {
                    if (indexes[j] < indexes[lru])
                        lru = j;
                }
                frame[lru] = pages[i];
                indexes[lru] = i;
            }
            page_faults++;
        }
    }
    free(frame);
    free(indexes);
    return page_faults;
}

int fifoPageReplacement(int pages[], int n, int capacity)
{
    int *frame = (int *)malloc(capacity * sizeof(int));
    int page_faults = 0;
    int index = 0;

    for (int i = 0; i < n; i++)
    {
        int found = 0;
        for (int j = 0; j < capacity; j++)
        {
            if (frame[j] == pages[i])
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            frame[index] = pages[i];
            index = (index + 1) % capacity;
            page_faults++;
        }
    }
    free(frame);
    return page_faults;
}

void display(float faults, float total_refs)
{
    printf("Page faults: %d\n", (int)faults);
    printf("Hit Ratio: %.2f\n", (total_refs - faults) / total_refs);
    printf("Miss ratio: %.2f\n", faults / total_refs);
}

int main()
{
    int capacity;
    printf("Enter cache capacity: ");
    scanf("%d", &capacity);
    int n;
    printf("Enter Number of Page References: ");
    scanf("%d", &n);
    int *pages = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("FIFO Page Replacement\n");
    display(fifoPageReplacement(pages, n, capacity), n);
    printf("LRU Page Replacement\n");
    display(lruPageReplacement(pages, n, capacity), n);
    printf("Optimal Page Replacement\n");
    display(optimalPageReplacement(pages, n, capacity), n);
    free(pages);
    return 0;
}