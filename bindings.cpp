#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "fcfs.h"
#include "sjfs_non_preemptive.h"
#include "sjfs_preemptive.h"
#include "priority_non_preemptive.h"
#include "priority_preemptive.h"
#include "round_robin.h"

namespace py = pybind11;

PYBIND11_MODULE(process_scheduling_chart, m) {
    m.def("FCFS_scheduling", &FCFS_scheduling);
    m.def("SJFS_No_Premption_scheduling", &SJFS_No_Premption_scheduling);
    m.def("SJFS_Premption_scheduling", &SJFS_Premption_scheduling);
    m.def("Priority_No_Premption_scheduling", &Priority_No_Premption_scheduling);
    m.def("Priority_Premption_scheduling", &Priority_Premption_scheduling);
    m.def("Round_Robin_scheduling", &Round_Robin_scheduling);
}
