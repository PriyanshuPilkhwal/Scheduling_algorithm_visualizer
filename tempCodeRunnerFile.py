
import tkinter as tk
from tkinter import ttk, messagebox, simpledialog
import process_scheduling_chart as psc  # pybind11 module

FONT_TITLE = ('Helvetica Neue', 20, 'bold')
FONT_SUB = ('Helvetica Neue', 14)
FONT_BTN = ('Helvetica Neue', 12, 'bold')

class SchedulingApp(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("CPU Scheduling Visualizer")
        self.geometry("900x700")
        self.num = 0
        self.algorithm = ''
        self.jobs = []

        # Screens
        self.frames = {}
        for F in (NumScreen, AlgoScreen):  # Exclude InputScreen here
            frame = F(self)
            self.frames[F] = frame
            frame.place(relwidth=1, relheight=1)
        self.show_frame(NumScreen)

    def show_frame(self, cls):
        self.frames[cls].tkraise()

class NumScreen(tk.Frame):
    def __init__(self, master):
        super().__init__(master)
        ttk.Label(self, text="Enter Number of Processes", font=FONT_TITLE).pack(pady=50)
        self.var = tk.IntVar(value=3)
        ttk.Entry(self, textvariable=self.var, font=FONT_SUB, width=5).pack()
        tk.Button(self, text="Next", command=self.next, font=FONT_BTN).pack(pady=20)

    def next(self):
        try:
            n = int(self.var.get())
            if n < 1:
                raise ValueError
            self.master.num = n
            self.master.show_frame(AlgoScreen)
        except:
            messagebox.showerror("Error", "Enter a valid positive integer")

class AlgoScreen(tk.Frame):
    def __init__(self, master):
        super().__init__(master)
        ttk.Label(self, text="Select Scheduling Algorithm", font=FONT_TITLE).pack(pady=50)
        self.combo = ttk.Combobox(
            self,
            values=["FCFS", "SJF", "SRJF", "Priority NP", "Priority P", "Round Robin"],
            font=FONT_SUB,
            state='readonly'
        )
        self.combo.current(0)
        self.combo.pack()
        tk.Button(self, text="Next", command=self.next, font=FONT_BTN).pack(pady=20)
        tk.Button(self, text="Back", command=lambda: master.show_frame(NumScreen), font=FONT_BTN).pack()

    def next(self):
        self.master.algorithm = self.combo.get()

        # Create fresh InputScreen with updated num and algorithm
        if InputScreen in self.master.frames:
            self.master.frames[InputScreen].destroy()
        input_screen = InputScreen(self.master)
        self.master.frames[InputScreen] = input_screen
        input_screen.place(relwidth=1, relheight=1)

        self.master.show_frame(InputScreen)

class InputScreen(tk.Frame):
    def __init__(self, master):
        super().__init__(master)
        self.master = master
        ttk.Label(self, text="Enter Process Details", font=FONT_TITLE).pack(pady=10)

        # Table headers
        self.table = ttk.Frame(self)
        self.table.pack()
        hdrs = ["Arrival", "Burst"]
        if master.algorithm.startswith("Priority"):
            hdrs.append("Priority")
        for c, h in enumerate(hdrs):
            ttk.Label(self.table, text=h, font=FONT_SUB, width=12).grid(row=0, column=c)

        # Rows for process details
        self.vars = []
        for i in range(master.num):
            arr = tk.IntVar(value=0)
            bst = tk.IntVar(value=1)
            row = [arr, bst]
            ttk.Entry(self.table, textvariable=arr, width=12).grid(row=i+1, column=0)
            ttk.Entry(self.table, textvariable=bst, width=12).grid(row=i+1, column=1)
            if master.algorithm.startswith("Priority"):
                pr = tk.IntVar(value=1)
                row.append(pr)
                ttk.Entry(self.table, textvariable=pr, width=12).grid(row=i+1, column=2)
            self.vars.append(row)

        # Quantum input if Round Robin
        if master.algorithm == "Round Robin":
            qf = ttk.Frame(self)
            qf.pack(pady=10)
            ttk.Label(qf, text="Time Quantum:", font=FONT_SUB).pack(side=tk.LEFT)
            self.quantum = tk.IntVar(value=2)
            ttk.Entry(qf, textvariable=self.quantum, width=5).pack(side=tk.LEFT)

        # Run and Back buttons
        btnf = ttk.Frame(self)
        btnf.pack(pady=20)
        tk.Button(btnf, text="Run", command=self.run, font=FONT_BTN).grid(row=0, column=0, padx=10)
        tk.Button(btnf, text="Back", command=lambda: master.show_frame(AlgoScreen), font=FONT_BTN).grid(row=0, column=1)

        # Results table
        self.res_table = ttk.Treeview(self, columns=("P","AT","BT","ST","CT","TAT","WT"), show='headings')
        for col in ("P","AT","BT","ST","CT","TAT","WT"): 
            self.res_table.heading(col, text=col)
        self.res_table.pack(pady=10)

        # Gantt chart canvas
        self.canvas = tk.Canvas(self, height=200, bg='white')
        self.canvas.pack(fill='x', padx=10, pady=10)

    def run(self):
        # Gather inputs
        procs = []
        prs = None
        for row in self.vars:
            a = row[0].get()
            b = row[1].get()
            procs.append((a, b))
            if len(row) == 3:
                if prs is None:
                    prs = []
                prs.append(row[2].get())

        n = self.master.num
        algo = self.master.algorithm

        # Schedule based on algorithm
        if algo == "FCFS":
            sched = psc.FCFS_scheduling(procs, n)
        elif algo == "SJF":
            sched = psc.SJFS_No_Premption_scheduling(procs, n)
        elif algo == "SRJF":
            sched = psc.SJFS_Premption_scheduling(procs, n)
        elif algo == "Priority NP":
            sched = psc.Priority_No_Premption_scheduling(procs, prs, n)
        elif algo == "Priority P":
            sched = psc.Priority_Premption_scheduling(procs, prs, n)
        else:
            sched = psc.Round_Robin_scheduling(procs, n, self.quantum.get())

        # Display results
        self.res_table.delete(*self.res_table.get_children())
        total_tat = total_wt = 0
        for pid, st, ct in sched:
            arr, bst = procs[pid-1]
            tat = ct - arr
            wt = st - arr
            total_tat += tat
            total_wt += wt
            self.res_table.insert('', tk.END, values=(pid, arr, bst, st, ct, tat, wt))

        # Draw Gantt chart
        self.canvas.delete('all')
        for pid, st, ct in sched:
            x0, y0 = st * 30 + 10, pid * 30
            x1, y1 = ct * 30 + 10, pid * 30 + 20
            self.canvas.create_rectangle(x0, y0, x1, y1, outline='black', fill='#add8e6')
            self.canvas.create_text((x0 + x1)//2, y0 + 10, text=f"P{pid}")

        # Show metrics
        avg_tat = total_tat / n
        avg_wt = total_wt / n
        messagebox.showinfo("Metrics", f"Avg Turnaround: {avg_tat:.2f}\nAvg Waiting: {avg_wt:.2f}")

if __name__ == "__main__":
    app = SchedulingApp()
    app.mainloop()
