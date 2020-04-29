#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <unistd.h>
#include <string.h>
#include "policies.h"

const int kMaxNameLength = 35;

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
