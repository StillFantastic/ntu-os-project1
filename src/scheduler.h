#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <unistd.h>
#include <algorithm>
#include <string.h>

const int kMaxNameLength = 35;

struct Process {
  char name[kMaxNameLength];
  int ready;
  int remain;
  int key;
  int spawned;
  pid_t pid;
};

bool CmpByReady(Process a, Process b);

#endif
