#include <iostream>
using namespace std;

#define totalprocess 4

struct process
{
    int at, bt, pr, pno;
};

process proc[50];

bool comp(process a, process b)
{
    if (a.at == b.at)
        return a.pr < b.pr;
    else
        return a.at < b.at;
}

void get_wt_time(int wt[])
{
    wt[0] = 0;
    for (int i = 1; i < totalprocess; i++)
    {
        wt[i] = wt[i - 1] + proc[i - 1].bt - proc[i].at;
        if (wt[i] < 0)
            wt[i] = 0;
    }
}

void get_tat_time(int tat[], int wt[])
{

    for (int i = 0; i < totalprocess; i++)
        tat[i] = proc[i].bt + wt[i];
}

void findGC()
{
    int wt[50], tat[50];

    double wAvg = 0, tAvg = 0;

    get_wt_time(wt);
    get_tat_time(tat, wt);

    int stime[50], ctime[50];

    stime[0] = proc[0].at;
    ctime[0] = stime[0] + tat[0];

    for (int i = 1; i < totalprocess; i++)
    {
        stime[i] = ctime[i - 1];
        ctime[i] = stime[i] + tat[i] - wt[i];
    }

    cout << "Process_no\tStart_time\tComplete_time\tTurn_Around_Time\tWaiting_Time" << endl;

    for (int i = 0; i < totalprocess; i++)
    {
        wAvg += wt[i];
        tAvg += tat[i];

        cout << proc[i].pno << "\t\t" << stime[i] << "\t\t" << ctime[i] << "\t\t" << tat[i] << "\t\t\t" << wt[i] << endl;
    }

    cout << "Average waiting time is : ";
    cout << wAvg / (float)totalprocess << endl;
    cout << "average turnaround time : ";
    cout << tAvg / (float)totalprocess << endl;
}

int main()
{
    int arrivalTime[] = {0, 0, 0, 0};
    int burstTime[] = {6, 8, 5, 7};
    int priority[] = {1, 3, 2, 4};

    for (int i = 0; i < totalprocess; i++)
    {
        proc[i].pno = i + 1;
        proc[i].at = arrivalTime[i];
        proc[i].bt = burstTime[i];
        proc[i].pr = priority[i];
    }

    sort(proc, proc + totalprocess, comp);
    findGC();

    return 0;
}
