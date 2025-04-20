from setuptools import setup, Extension
import pybind11
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "process_scheduling_chart",  # Name of the Python module
        [
            "bindings.cpp",
            "fcfs.cpp",
            "sjfs_preemptive.cpp",
            "sjfs_non_preemptive.cpp",
            "priority_preemptive.cpp",
            "priority_non_preemptive.cpp",
            "round_robin.cpp"
        ],
        include_dirs=["."],  # Includes the current directory for header files
        cxx_std=17,
    ),
]

setup(
    name="process_scheduling_chart",
    version="0.1",
    author="Your Name",
    description="CPU Scheduling Algorithms in C++ with Pybind11",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)
