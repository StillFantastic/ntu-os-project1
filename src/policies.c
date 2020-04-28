#include "policies.h"

void RunFIFO(struct Process *ps, int n) {
  int cur_time = 0;
  for (int i = 0; i < n; i++) {
    while (cur_time < ps[i].ready) {
      cur_time++;
      UNIT_TIME;
    }
    SpawnProcess(&ps[i]);
    // Prevent preemption
    SetProcessPriority(ps[i].pid, 99); 
    wait(NULL);
    cur_time += ps[i].remain;
    ps[i].remain = 0;
  }
}
