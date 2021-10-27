# O.S.-Asssigment2
1 Overview
In this project, you are going to build a “discrete-time event simulator” (see site below) for a
number of CPU scheduling algorithms on a single CPU system. The goal of this project is to
compare and assess the impact of different scheduling algorithms on different performance
metrics, and across multiple workloads.
https://en.wikipedia.org/wiki/Discrete-event_simulation
1.1 CPU Scheduling Algorithms
We are going to implement the following CPU scheduling algorithms that we learned in class:
1. First-Come First-Served (FCFS) [non-preemptive]
2. Shortest Remaining Time First (SRTF) [preemptive by comparison of run time left]
3. Round Robin, with different quantum values (RR) [preemptive by quantum]
1.2 Performance Metrics
We are interested in computing the following metrics, for each experiment:
• The average turnaround time
• The total throughput (number of processes done per unit time)
• The CPU utilization
• The average number of processes (queue length) in the ready queue
Note: There is a relationship between:
- average queue length n,
- average arrival time λ (in processes/second), and
Page 2 of 4
- average waiting time for a single process W (in seconds):
 n = λW.
This relationship allows computing any of these quantities from the other two.
2 The Simulator
A discrete-time event simulation models the operation of a system as a discrete sequence of
events in time. Each event occurs at a particular instant in time and marks a change of state
in the system. Between consecutive events, no change in the system is assumed to occur;
thus the simulation time can directly jump to the occurrence time of the next event, which is
called next-event time progression.
Your simulator needs to generate a list of CPU-bound processes (no I/O happens for them).
For each process, we need to generate its arrival time and its requested service time (or
burst time). We can assume that processes arrive with an average rate λ that follows a
Poisson process (hence exponential inter-arrival times). We will vary λ to simulate different
loads. The service times are generated according to an exponential distribution (more detail
below).
The simulator should stop after handling 10,000 processes to completion (without stopping
the arrival of new processes), then it should output the statistics (i.e., the metrics above).
Events (e.g., process arrival, process completion, time-slice occurrence) that occur cause the
simulator to update its current state (e.g., CPU busy/idle, number of processes in the ready
queue, etc.). To keep track and handle events in the right order, we keep events in a priority
list (called the “Events List”) that describes the future events and is kept sorted by the time of
each event.
The simulator keeps a clock that represents the current system time, which takes the time
from the event at the head of the Events List. Notice that when an event is handled at its
assigned time, one or more future events may be added to the Events List. For example,
when a process gets serviced by the CPU, another process can start executing (if one is
waiting in the “Process Ready Queue”) and under FCFS, we know exactly when this process
would finish, so we can schedule a completion event in the future and place it in the Events
List. Notice that time hops between events, so you will need to update your simulator clock
accordingly.
The simulator must take a few command-line arguments. The first one is to indicate the
scheduling algorithm, a 1 through 3 value based on the list above. Also, it should take other
arguments such as the average arrival rate, the average service time, and the quantum
interval (for RR). Running the simulator with no arguments should display the arguments
usage.
Each scheduler will need to maintain a queue (the “Process Ready Queue”) for the ready
processes that are waiting for the CPU. A scheduler will select a process to run next based on
the scheduling policy. Clearly, this queue should not be confused with the simulation’s Events
List that is used to hold events to be handled in the future. 
Page 3 of 4
3 The Runs
We will vary the average arrival rate, λ, of processes from 1 process per second to 30
processes per second (based on a Poisson distribution). The service time is chosen
according to an exponential distribution with an average service time of 0.06 sec.
For each value of λ, we need to compare the performance of each scheduler, based on the
metrics above. It is recommended that you write a simple batch file (script) that would run
those experiments and put the results in a file (that you can later import into a spreadsheet to
plot the values).
Example script (assume your program is called sim and it creates the output file sim.data):
#!/bin/bash
rm sim.data
for ((i = 1; i <= 30; i++)); do
 ./sim 1 $i 0.06 0.01
 cp sim.data /data/sim-1-$i-001.data
done
NOTICE:
The “sim” program called in the above script has the following four arguments:
• First: the scheduling algorithm number (1 to 3),
• Second: the number of processes per second as the arrival rate,
• Third: the average burst time for processes,
• Fourth: the quantum value (used for RR only).
This example bash script will run the simulator using FCFS (indicated by the value 1 in the
first argument) for 30 different values of λ, using 0.06 as the average service time and a
quantum value of 0.01 (which is ignored in other algorithms, except in Round Robin). Then,
the script will move the sim.data file to a safe place for later use.
With the Round Robin algorithm, a fourth argument is supplied to indicate the quantum value
to be used. Use 2 different values of quantum: 0.01 and 0.2 (i.e., make two different runs).
Remember, if a process finishes before its quantum expires, the CPU should be scheduled for
the next process right away. 
