// priority_preemptive.cpp
#include "priority_preemptive.h"

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

using P = pair<int, int>;

// Preemptive priority scheduling
vector<vector<int>> Priority_Premption_scheduling(
    vector<P>& processes,
    vector<int>& priority,
    int n
)
{
    // Tuple: (arrival, (index, (burst, priority)))
    using T = pair<
        int,
        pair<int, pair<int, int>>
    >;

    vector<T> proc;
    vector<vector<int>> ans;

    // Build process list and initial remaining times
    for (int i = 0; i < n; ++i)
    {
        proc.push_back({
            processes[i].first,
            { i, { processes[i].second, priority[i] } }
        });
    }

    // Sort by arrival time
    sort(proc.begin(), proc.end());

    vector<int> remain(n);
    vector<int> startTime(n, -1);
    vector<int> completionTime(n, 0);

    // Initialize remaining burst times
    for (int i = 0; i < n; ++i)
    {
        remain[i] = proc[i].second.second.first;
    }

    int currentTime = 0;
    int completedCount = 0;

    // Main scheduling loop
    while (completedCount < n)
    {
        int idx = -1;
        int maxPriority = INT_MIN;

        // Find highest-priority ready process
        for (int i = 0; i < n; ++i)
        {
            if (remain[i] > 0
                && proc[i].first <= currentTime
                && proc[i].second.second.second > maxPriority
            )
            {
                maxPriority = proc[i].second.second.second;
                idx = i;
            }
        }

        // If no process is ready, advance time
        if (idx == -1)
        {
            ++currentTime;
        }
        else
        {
            // Record first response time
            if (startTime[idx] == -1)
                startTime[idx] = currentTime;

            // Log one time unit in Gantt chart
            ans.push_back({ idx + 1, currentTime, currentTime + 1 });

            // Execute for one time unit
            --remain[idx];
            ++currentTime;

            // If process completes
            if (remain[idx] == 0)
            {
                ++completedCount;
                completionTime[idx] = currentTime;
            }
        }
    }

    return ans;
}