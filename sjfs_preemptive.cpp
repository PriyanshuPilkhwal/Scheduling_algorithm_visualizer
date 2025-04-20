// sjfs_preemptive.cpp

#include "sjfs_preemptive.h"
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

using P = pair<int, int>;

// Preemptive Shortest Remaining Time First (SRTF) Scheduling
vector<vector<int>> SJFS_Premption_scheduling(
    vector<P>& processes,
    int n
)
{
    // Helper tuple: (arrival_time, (index, burst_time))
    using S = pair<int, pair<int, int>>;

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

    int currentTime = 0;
    int completedCount = 0;

    // Main scheduling loop
    while (completedCount < n)
    {
        int idx = -1;
        int minRemaining = INT_MAX;

        // Find ready process with shortest remaining time
        for (int i = 0; i < n; ++i)
        {
            if (remain[i] > 0
                && proc[i].first <= currentTime
                && remain[i] < minRemaining
            )
            {
                minRemaining = remain[i];
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
            ans.push_back({
                idx + 1,
                currentTime,
                currentTime + 1
            });

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
