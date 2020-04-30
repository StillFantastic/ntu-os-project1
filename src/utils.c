#include "utils.h"
#include <errno.h>
#define _GNU_SOURCE

void AssignCPU(pid_t pid, int core) {
  if (core >= CPU_SETSIZE) {
    fprintf(stderr, "AssignCPU: core exceeds the number of cpu cores\n");
    exit(1);
  }

  cpu_set_t mask;
  CPU_ZERO(&mask);
  CPU_SET(core, &mask);
  if (sched_setaffinity(pid, sizeof(mask), &mask) != 0) {
    fprintf(stderr, "AssignCPU: set affinity failed\n");
    exit(1);
  }
}

void SetProcessPriority(pid_t pid, int value) {
	if (kill(pid, 0) == -1)
		return;
  if (value > sched_get_priority_max(SCHED_FIFO)) {
    fprintf(stderr, "SetProcessPriority: priority exceeds max allowed priority\n");
    exit(1);
  }

  struct sched_param param;
  param.sched_priority = value;
  if (sched_setscheduler(pid, SCHED_FIFO, &param) != 0) {
    printf("errno: %s\n", strerror(errno));
    fprintf(stderr, "SetProcessPriority: set scheduler failed\n");
    exit(1);
  }
}

void GetTimestamp(struct timespec *ts) {
  clock_gettime(CLOCK_REALTIME, ts);
}

void PrintTimestamp(pid_t pid, struct timespec *start, struct timespec *end) {
  syscall(336, pid, start->tv_sec, start->tv_nsec, end->tv_sec, end->tv_nsec);
}

int SpawnProcess(struct Process *ps, int pri) {
  pid_t pid = fork();

  if (pid < 0) {
    fprintf(stderr, "SpawnProcess: fork error\n");
    exit(1);
  } else if (pid == 0) {
    ps->pid = getpid();
    printf("%s %d\n", ps->name, ps->pid);
    struct timespec start, end;
    GetTimestamp(&start);
    for (int i = 0; i < ps->remain; i++) {
      UNIT_TIME;
    }
    GetTimestamp(&end);
    PrintTimestamp(ps->pid, &start, &end);
    exit(0);
  } else {
    ps->pid = pid;
    AssignCPU(ps->pid, 1);
    SetProcessPriority(ps->pid, pri);
    ps->spawned = 1;
    return pid;
  }
}
