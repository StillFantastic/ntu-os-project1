#ifndef UTILS_H_
#define UTILS_H_

#define _GNU_SOURCE
#define UNIT_TIME { volatile unsigned long i; for(i=0;i<1000000UL;i++); } 

#include <sched.h>
#include <unistd.h>
#include <time.h>
#include <sys/syscall.h>
#include <stdio.h>
#include "scheduler.h"

void AssignCPU(pid_t pid, int core);
void SetProcessPriority(pid_t pid, int value);
int SpawnProcess(struct Process *ps, int pri);
void GetTimestamp(struct timespec *ts);

#endif
