

#include <stdio.h>
#include <limits.h>

struct Process
{
    int pid;
    int bt;
    int art;
};

void findWaitingTime(struct Process proc[], int n, int wt[])
{
    int rt[n];

    for (int i = 0; i < n; i++)
        rt[i] = proc[i].bt;

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    int check = 0;

    while (complete != n)
    {

        for (int j = 0; j < n; j++)
        {
            if ((proc[j].art <= t) &&
                (rt[j] < minm) && rt[j] > 0)
            {
                minm = rt[j];
                shortest = j;
                check = 1;
            }
        }

        if (check == 0)
        {
            t++;
            continue;
        }

        rt[shortest]--;

        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        if (rt[shortest] == 0)
        {

            complete++;
            check = 0;

            finish_time = t + 1;

            wt[shortest] = finish_time - proc[shortest].bt - proc[shortest].art;

            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }

        t++;
    }
}

void findTurnAroundTime(struct Process proc[], int n, int wt[], int tat[])
{

    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];
}

void findavgTime(struct Process proc[], int n)
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    findWaitingTime(proc, n, wt);

    findTurnAroundTime(proc, n, wt, tat);

    printf(" P\t\t"
           "BT\t\t"
           "WT\t\t"
           "TAT\t\t\n");

    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf(" %d\t\t"
               "%d\t\t %d"
               "\t\t %d\n",
               proc[i].pid,
               proc[i].bt, wt[i], tat[i]);
    }

    printf("\nAverage waiting time = "
           "%f",
           (float)total_wt / (float)n);
    printf("\nAverage turn around time = "
           "%f",
           (float)total_tat / (float)n);
}

int main()
{
    struct Process proc[] = {{1, 6, 2}, {2, 2, 5}, {3, 8, 1}, {4, 3, 0}, {5, 4, 4}};
    int n = sizeof(proc) / sizeof(proc[0]);

    findavgTime(proc, n);
    return 0;
}
