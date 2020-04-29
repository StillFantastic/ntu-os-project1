#include "scheduler.h"

int CmpByReady(const void *a, const void *b) {
  const struct Process *p1 = (const struct Process *)a;
  const struct Process *p2 = (const struct Process *)b;
  if (p1->ready < p2->ready) return -1;
  if (p1->ready > p2->ready) return 1;
  if (p1->key < p2->key) return -1;
  if (p1->key > p2->key) return -1;
  return 0;
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

  qsort((void *)process, n, sizeof(struct Process), CmpByReady);
  
  // Assign scheduler process to run on core 0
  AssignCPU(getpid(), 0);
  // Set to highest priority to prevent preemption
  SetProcessPriority(getpid(), 99);

  if (strcmp(policy, "FIFO") == 0) RunFIFO(process, n);

  return 0;
}
