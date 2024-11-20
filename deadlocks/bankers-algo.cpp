#include <iostream>
#include <vector>
using namespace std;

void displayMatrix(const vector<vector<int>> &matrix, const string &name)
{
    cout << "Matrix " << name << ":" << endl;
    for (const auto &row : matrix)
    {
        for (int val : row)
            cout << val << " ";
        cout << endl;
    }
}

bool isSafe(const vector<vector<int>> &allocation, const vector<vector<int>> &max, vector<int> available, vector<vector<int>> &need, vector<int> &finishOrder)
{
    int numProc = allocation.size();
    vector<bool> finish(numProc, false);
    vector<int> work = available;
    while (true)
    {
        bool changed = false;
        for (int i = 0; i < numProc; ++i)
        {
            if (!finish[i])
            {
                bool canAllocate = true;
                for (int j = 0; j < need[i].size(); ++j)
                {
                    if (need[i][j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate)
                {
                    finish[i] = true;
                    finishOrder.push_back(i);
                    for (int j = 0; j < need[i].size(); ++j)
                        work[j] += allocation[i][j];
                    changed = true;
                }
            }
        }
        if (!changed)
            break;
    }
    for (bool f : finish)
    {
        if (!f)
            return false;
    }
    return true;
}

bool requestResources(int process, vector<int> &request, vector<vector<int>> &allocation, vector<vector<int>> &need, vector<int> &available, const vector<vector<int>> &max)
{
    for (int r = 0; r < request.size(); r++)
    {
        if (request[r] > need[process][r])
        {
            cout << "Error: Process has exceeded its maximum claim." << endl;
            return false;
        }
        
    }

    for (int r = 0; r < request.size(); r++)
    {
        if (request[r] > available[r])
        {
            cout << "Error: Resources are not available." << endl;
            return false;
        }
    }

    for (int r = 0; r < request.size(); r++)
    {
        available[r] -= request[r];
        allocation[process][r] += request[r];
        need[process][r] -= request[r];
    }

    vector<int> finishOrder;
    if (isSafe(allocation, max, available, need, finishOrder))
    {
        cout << "Request can be granted. System remains in a safe state." << endl;
        return true;
    }
    else
    {
        for (int r = 0; r < request.size(); r++)
        {
            available[r] += request[r];
            allocation[process][r] -= request[r];
            need[process][r] += request[r];
        }
        cout << "Request cannot be granted. System would be in an unsafe state." << endl;
        return false;
    }
}

int main()
{
    int numProc, numReso;
    cout << "Enter the number of processes: ";
    cin >> numProc;
    cout << "Enter the number of resources: ";
    cin >> numReso;

    vector<vector<int>> allocation(numProc, vector<int>(numReso));
    vector<vector<int>> maxDemand(numProc, vector<int>(numReso));
    vector<int> available(numReso);

    cout << "Enter the Allocation matrix:\n";
    for (int i = 0; i < numProc; ++i)
    {
        for (int j = 0; j < numReso; ++j)
            cin >> allocation[i][j];
    }

    cout << "Enter the Max Demand matrix:\n";
    for (int i = 0; i < numProc; ++i)
    {
        for (int j = 0; j < numReso; ++j)
            cin >> maxDemand[i][j];
    }

    cout << "Enter the Available resources:\n";
    for (int j = 0; j < numReso; ++j)
        cin >> available[j];

    vector<vector<int>> need(numProc, vector<int>(numReso));
    for (int i = 0; i < numProc; ++i)
    {
        for (int j = 0; j < numReso; ++j)
            need[i][j] = maxDemand[i][j] - allocation[i][j];
    }

    vector<int> finishOrder;
    if (isSafe(allocation, maxDemand, available, need, finishOrder))
    {
        cout << "System is in a safe state.\n";
        cout << "\nExecution Order of Processes:\n";
        for (int process : finishOrder)
            cout << "P" << process << " ";
        cout << endl;
    }
    else
        cout << "System is in an unsafe state.\n";

    cout << endl;
    displayMatrix(need, "Need");

    int process;
    cout << "Enter the process number making the request: ";
    cin >> process;

    vector<int> request(numReso);
    cout << "Enter the request for resources:\n";
    for (int j = 0; j < numReso; ++j)
        cin >> request[j];

    if (requestResources(process, request, allocation, need, available, maxDemand))
    {
        cout << "Request granted.\n";
    }
    else
    {
        cout << "Request denied.\n";
    }

    return 0;
}