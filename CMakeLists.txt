cmake_minimum_required(VERSION 3.15)

project(process_scheduling_chart)

# Find Python and pybind11
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)

# Include directories (usually not needed if using pybind11 package correctly)
include_directories(${Python3_INCLUDE_DIRS})

# Add all source files (bindings + all the scheduling algorithm files)
pybind11_add_module(process_scheduling_chart 
    bindings.cpp 
    fcfs.cpp 
    sjfs_preemptive.cpp
    sjfs_non_preemptive.cpp
    priority_non_preemptive.cpp
    priority_preemptive.cpp
    round_robin.cpp
)
