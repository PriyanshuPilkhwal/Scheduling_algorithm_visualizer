#include "fcfs.h"

#include <vector>
#include <algorithm>
#include <climits>
#include <tuple>


using namespace std;

using P = pair<int, int>;

// FCFS Scheduling: Returns vector of {pid, start time, completion time}
vector<vector<int>>FCFS_scheduling(vector<P>& processes, int n)
{
    vector<vector<int>> ans;

    // Sort by arrival time, then by process ID (1-based)
    vector<tuple<int, int, int>> proc; // (arrival, burst, index)
    for (int i = 0; i < n; ++i)
    {
        proc.push_back({processes[i].first, processes[i].second, i});
    }
    sort(proc.begin(), proc.end());

    int currentTime = 0;
    for (auto [at, bt, idx] : proc)
    {
        if (currentTime < at) currentTime = at;
        int st = currentTime;
        int ct = st + bt;
        ans.push_back({idx + 1, st, ct});
        currentTime = ct;
    }

    return ans;
}
