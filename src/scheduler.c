#include "scheduler.h"

bool CmpByReady(struct Process a, struct Process b) {
  if (a.ready == b.ready)
    return a.key < b.key;
  return a.ready < b.ready;
}

int main() {
  char policy[6];
  // The number of processes
  int n; 

  scanf("%s", policy);
  scanf("%d", &n);

  struct Process process[n];
  for (int i = 0; i < n; i++) {
    scanf("%s%d%d", process[i].name, &process[i].ready, &process[i].remain);
    process[i].key = i;
  }

  sort(process, process + n, CmpByReady);
  
  // Assign scheduler process to run on core 0
  AssignCPU(getpid(), 0);
  // Set to highest priority to prevent preemption
  SetProcessPriority(getpid(), 99);

  if (strcmp(policy, "FIFO") == 0) RunFIFO(process, n);

  return 0;
}
