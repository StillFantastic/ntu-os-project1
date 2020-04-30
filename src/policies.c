#include "policies.h"
#include "heap.h"

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

void RunSJF(struct Process *ps, int n) {
  int cur_ps = 0;
  int cur_time = 0;
  struct heap *h;
  heap_init(h);
  while (cur_ps < n || h->count) {
    if (h->count == 0) {
      while (true) {
        while (cur_time < ps[cur_ps].ready) {
          cur_time++;
          UNIT_TIME;
        }
        heap_push(h, &ps[cur_ps]);
        cur_ps++;
        if (cur_ps == n || ps[cur_ps].ready != ps[cur_ps - 1].ready)
          break;
      }
    }

    while (cur_ps < n && cur_time >= ps[cur_ps].ready) {
      heap_push(h, &ps[cur_ps]);
      cur_ps++;
    }

    struct Process *p = heap_front(h);
    SpawnProcess(p);
    SetProcessPriority(p->pid, 99);
    wait(NULL);
    cur_time += p->remain;
    p->remain = 0;
  }
}

void RunPSJF(struct Process *ps, int n) {
  int cur_ps = 0;
  struct heap *h;
  struct Process *running_ps = NULL;
  for (int cur_time = 0; ; cur_time++) {
    if (running_ps && running_ps->remain == 0) {
      wait(NULL);
      if (cur_ps == n && !heap_front(h))
        return;
      p = NULL; 
    }

    while (cur_ps < n && ps[cur_ps].ready < cur_time) {
      heap_push(h, &ps[cur_ps]);
      cur_ps++;
    }
    if (running_ps) {
      struct Process *preemptive = heap_front(h);
      if (preemptive->remain < running_ps->remain) {
        SetProcessPriority(running_ps->pid, 1);
        heap_push(h, running_ps);
        running_ps = heap_front(h);
        if (running_ps->spawned == 0)
          SpawnProcess(running_ps); 
        SetProcessPriority(running_ps->pid, 99);
      }
    }

    if (running_ps == NULL && h->count != 0) {
      running_ps = heap_front(h);
      if (running_ps->spawned == 0)
        SpawnProcess(p);
    }

    UNIT_TIME;
    if (running_ps)
      running_ps->remain--;
  }
}
