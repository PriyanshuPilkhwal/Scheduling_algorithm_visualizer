
**CPU Scheduling Visualizer**

A GUI-based visualization tool for common CPU scheduling algorithms, combining a C++ backend (with Pybind11 bindings) and a Python frontend (Tkinter).

---

## Table of Contents

1. [Project Structure](#project-structure)
2. Languages & Tools
3. [Libraries & Dependencies](#libraries--dependencies)
4. [Installation & Setup](#installation--setup)
5. [Building the Extension (C++)](#building-the-extension-c)
6. [Running the GUI (Python)](#running-the-gui-python)
7. [Usage Examples](#usage-examples)
8. [Contributing](#contributing)
9. [Contact](#contact)

---

## Project Structure

```text
├── bindings.cpp           # Pybind11 module definitions
├── fcfs.cpp               # FCFS algorithm implementation
├── fcfs.h                 # FCFS function declaration
├── sjfs_non_preemptive.cpp# Non-preemptive SJF implementation
├── sjfs_non_preemptive.h  # SJF non-preemptive declaration
├── sjfs_preemptive.cpp    # Preemptive SJF implementation
├── sjfs_preemptive.h      # SJF preemptive declaration
├── priority_non_preemptive.cpp
├── priority_non_preemptive.h
├── priority_preemptive.cpp
├── priority_preemptive.h
├── round_robin.cpp        # Round Robin implementation
├── round_robin.h          # Round Robin declaration
├── setup.py               # Build script for Python extension
├── main.py                # Tkinter GUI entry point
└── README.md              # Project documentation
```

## Languages & Tools

- **C++ (17)**: Algorithm implementations and Pybind11 bindings.
- **Python (3.10+)**: GUI built with Tkinter and binding usage.
- **Pybind11**: Exposes C++ functions as Python-callable.
- **Tkinter**: Standard Python library for GUIs.
- **Build Tools**: Visual Studio Build Tools (Windows) or GCC/Clang (Linux/Mac).
- **Git & GitHub**: Version control and collaboration.

## Libraries & Dependencies

- **C++**:
  - `<vector>`, `<tuple>`, `<algorithm>`, `<climits>`
  - Pybind11 headers (`pybind11/pybind11.h`, `pybind11/stl.h`)
- **Python**:
  - `pybind11` (install via `pip install pybind11`)
  - `tkinter` (usually included with Python)

## Installation & Setup

1. **Clone the repository**:

   ```bash
   git clone https://github.com/PriyanshuPilkhwal/Scheduling_algorithm_visualizer.git
   cd cpu-scheduling-visualizer
   ```

2. **Install Python dependencies**:

   ```bash
   pip install pybind11
   ```

## Building the Extension (C++)

Build the C++ extension in-place:

```bash
python setup.py build_ext --inplace
```

This generates the `process_scheduling_chart` extension module (`.pyd` on Windows or `.so` on Linux/Mac).

## Running the GUI (Python)

Once the extension builds successfully, run:

```bash
python main.py
```

You will be prompted to:

1. Enter the number of processes.
2. Select a scheduling algorithm.
3. Input arrival times, burst times, (and priorities/quantum if applicable).
4. View the computed schedule and Gantt chart.

## Usage Examples

```python
import process_scheduling_chart as psc

# Example: FCFS
procs = [(0, 5), (2, 3), (4, 1)]
schedule = psc.FCFS_scheduling(procs, len(procs))
print(schedule)
```

## Contributing

1. Fork the repo.
2. Create a feature branch (`git checkout -b feature/my-feature`).
3. Commit your changes (`git commit -m 'Add new algorithm'`).
4. Push to the branch (`git push origin feature/my-feature`).
5. Open a Pull Request.

Please adhere to the existing coding style and include tests/examples.


## Contact

Created by [Priyanshu_Pilkhwal](https://github.com/PriyanshuPilkhwal).\
Feel free to open issues or reach out via GitHub.

