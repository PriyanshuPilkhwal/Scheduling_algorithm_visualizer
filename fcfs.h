#pragma once
#include <vector>
#include <utility>

using P = std::pair<int, int>;

std::vector<std::vector<int>> FCFS_scheduling(std::vector<P>& processes, int n);
