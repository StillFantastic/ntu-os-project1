# NTU OS Project - Process Scheduler

## Prepare
```
git clone https://github.com/StillFantastic/ntu-os-project1.git
cd ntu-os-projcet1
make
```

## Program Input
* The program will get the input parameters from the standard input. 
```
// the scheduling policy, one of the following strings: FIFO, RR, SJF, PSJF.
N // the number of processes
N1 R1 T1
N2 R2 T2
…
Nn Rn Tn
//Ni - a character string with a length less than 32 bytes, specifying the name of the i-th process.
//Ri - a non-negative integer, specifying the ready time of the i-th process.
//Ti - a non-negative integer, specifying the execution time of the i-th process. 
```
For example, a input for FIFO scheduling with three processes might look like this:
```
FIFO
3
P1 1 10
P2 2 5
P3 2 7 
```

## Program Output
* In each child process, show its name and PID to the standard output with the following format:
```
NAME PID
//NAME - the name of this process specified by the input
//PID - the process id of this process 
```
In Linux kernel, show the start and finish of each process by printk with the following format:
```
TAG PID ST FT
//TAG - the tag to identify the message of this project.
//PID - the process ID of this process
//ST - the start time of this process in the format seconds.nanoseconds.
//FT - the finish time of this process in the format seconds.nanoseconds. 
```
The output of the program might look like this:
```
P1 4007
P2 4008
P3 4009 
```
The output from the command dmesg might contain:

```
[Project1] 4007 1394530429.657899070 1394530430.004979285
[Project1] 4008 1394530429.668132665 1394530430.218223930
[Project1] 4009 1394530429.676547365 1394530430.221544405 
```
