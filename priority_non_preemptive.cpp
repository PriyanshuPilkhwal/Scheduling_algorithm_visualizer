// priority_non_preemptive.cpp
#include "priority_non_preemptive.h"

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

using P = pair<int, int>;

// Non-preemptive priority scheduling
vector<vector<int>> Priority_No_Premption_scheduling(
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

    // Build process list
    for (int i = 0; i < n; ++i)
    {
        proc.push_back({
            processes[i].first,
            {
                i,
                { processes[i].second, priority[i] }
            }
        });
    }

    // Sort by arrival time
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
        int maxPriority = INT_MIN;

        // Find highest-priority ready process
        for (int i = 0; i < n; ++i)
        {
            if (!done[i]
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
            // Schedule selected process
            startTime[idx] = currentTime;
            completionTime[idx] = startTime[idx] + proc[idx].second.second.first;

            ans.push_back({
                idx + 1,
                startTime[idx],
                completionTime[idx]
            });

            // Update time and counters
            currentTime = completionTime[idx];
            done[idx] = true;
            ++completedCount;
        }
    }

    return ans;
}
