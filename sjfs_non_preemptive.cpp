// sjfs_non_preemptive.cpp

#include "sjfs_non_preemptive.h"

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

using P = pair<int, int>;

// Non-preemptive Shortest Job First (SJF) Scheduling
vector<vector<int>> SJFS_No_Premption_scheduling(
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

    vector<int> startTime(n, 0);
    vector<int> completionTime(n, 0);
    vector<bool> done(n, false);

    int currentTime = 0;
    int completedCount = 0;

    // Main scheduling loop
    while (completedCount < n)
    {
        int idx = -1;
        int minBurst = INT_MAX;

        // Find the ready process with the shortest burst time
        for (int i = 0; i < n; ++i)
        {
            if (!done[i]
                && proc[i].first <= currentTime
                && proc[i].second.second < minBurst
            )
            {
                minBurst = proc[i].second.second;
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
            // Schedule process
            startTime[idx] = currentTime;
            completionTime[idx] = startTime[idx] + proc[idx].second.second;

            ans.push_back({
                idx + 1,
                startTime[idx],
                completionTime[idx]
            });

            // Update state
            currentTime = completionTime[idx];
            done[idx] = true;
            ++completedCount;
        }
    }

    return ans;
}
