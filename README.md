# CPU-Scheduling-Simulator

This projecct Simulate the scheduling of processes on the processor with different Scheduling Algorithms. The Scheduling Algorithms simulated in this project are:
1. FCFS (First Come First Serve)
2. SJF (Shortest Job First) - Preemptive
3. PRIORITY - Preemptive
4. RR (Round Robin)

## Usage
Give input to program through file "prod.dat". Enter Input in "prod.dat" in following format:
1. First line is number of processes N.
2. Each of next N lines contain ProcessID, Priority, Arrival time, followed by a sequence of CPU burst, IO burst. -1 indicates end of line. All these values are separared by comma. For eg: 2, 3, 4, 5, 2, 4, 3, 7, -1 indicates a process with id=2, priority 3, arrival time 4 and CPU bursts of 5, 4 and 7 interleaving with IO bursts of 2 and 3.
This program will display progress of each process through a display with following symbols
C: running (CPU scheduled)
W: waiting for CPU
B: blocked for IO
R: running on IO.
Value for time quantum is one.
