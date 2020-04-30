#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "policies.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define kMaxNameLength 35

struct Process {
  char name[kMaxNameLength];
  int ready;
  int remain;
  int key;
  int spawned;
  pid_t pid;
};

int CmpByReady(const void *a, const void *b);

#endif
