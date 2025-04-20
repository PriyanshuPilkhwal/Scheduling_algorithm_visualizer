// round_robin.cpp

#include "round_robin.h"


#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

using P = pair<int, int>;

// Round Robin scheduling algorithm
vector<vector<int>> Round_Robin_scheduling(
    vector<P>& processes,
    int n,
    int quantum
)
{
    // Tuple: (arrival, (index, burst))
    using S = pair<
        int,
        pair<int, int>
    >;

    vector<S> proc;
    vector<vector<int>> ans;

    // Build and sort process list by arrival time
    for (int i = 0; i < n; ++i)
    {
        proc.push_back({
            processes[i].first,
            { i, processes[i].second }
        });
    }
    sort(proc.begin(), proc.end());

    vector<int> remain(n);
    vector<int> startTime(n, -1);
    vector<int> completionTime(n, 0);

    // Initialize remaining burst times
    for (int i = 0; i < n; ++i)
    {
        remain[i] = proc[i].second.second;
    }

    queue<int> q;
    int currentTime = 0;
    int idx = 0;
    int completedCount = 0;

    // Main scheduling loop
    while (completedCount < n)
    {
        // Enqueue processes that have arrived
        while (idx < n && proc[idx].first <= currentTime)
        {
            q.push(idx);
            ++idx;
        }

        // If no ready process, advance time
        if (q.empty())
        {
            ++currentTime;
            continue;
        }

        // Dequeue next process
        int i = q.front();
        q.pop();

        // Record first response time
        if (startTime[i] == -1)
            startTime[i] = currentTime;

        // Determine run duration
        int runTime = min(quantum, remain[i]);

        // Record execution in Gantt chart data
        ans.push_back({
            i + 1,
            currentTime,
            currentTime + runTime
        });

        // Execute process
        currentTime += runTime;
        remain[i] -= runTime;

        // Enqueue any newly arrived processes
        while (idx < n && proc[idx].first <= currentTime)
        {
            q.push(idx);
            ++idx;
        }

        // If not yet completed, requeue
        if (remain[i] > 0)
        {
            q.push(i);
        }
        else
        {
            // Mark completion
            completionTime[i] = currentTime;
            ++completedCount;
        }
    }

    return ans;
}
