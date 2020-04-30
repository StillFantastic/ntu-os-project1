#include "policies.h"
#include "heap.h"

void RunFIFO(struct Process *ps, int n) {
  int cur_time = 0;
  for (int i = 0; i < n; i++) {
    while (cur_time < ps[i].ready) {
      cur_time++;
      UNIT_TIME;
    }
    SpawnProcess(&ps[i], 99);
    wait(NULL);
    cur_time += ps[i].remain;
    ps[i].remain = 0;
  }
}

void RunSJF(struct Process *ps, int n) {
  int cur_ps = 0;
  int cur_time = 0;
  struct heap h;
  heap_init(&h);
  while (cur_ps < n || h.count) {
    if (h.count == 0) {
      while (1) {
        while (cur_time < ps[cur_ps].ready) {
          cur_time++;
          UNIT_TIME;
        }
        heap_push(&h, &ps[cur_ps]);
        cur_ps++;
        if (cur_ps == n || ps[cur_ps].ready != ps[cur_ps - 1].ready)
          break;
      }
    }

    while (cur_ps < n && cur_time >= ps[cur_ps].ready) {
      heap_push(&h, &ps[cur_ps]);
      cur_ps++;
    }

    struct Process *p = heap_front(&h);
    heap_pop(&h);
    int pid = SpawnProcess(p, 99);
    wait(NULL);
    cur_time += p->remain;
    p->remain = 0;
  }
}

void RunPSJF(struct Process *ps, int n) {
  int cur_ps = 0;
  int pid;
  struct heap h;
  struct Process *running_ps = NULL;
  heap_init(&h);
  for (int cur_time = 0; ; cur_time++) {
    if (running_ps && running_ps->remain == 0) {
      wait(NULL);
      if (cur_ps == n && h.count == 0)
        return;
      running_ps = NULL; 
    }

    while (cur_ps < n && ps[cur_ps].ready <= cur_time) {
      heap_push(&h, &ps[cur_ps]);
      cur_ps++;
    }
    if (running_ps) {
      struct Process *preemptive = heap_front(&h);
      if (preemptive->remain < running_ps->remain) {
        SetProcessPriority(running_ps->pid, 1);
        heap_push(&h, running_ps);
				heap_pop(&h);
        running_ps = preemptive;
        if (running_ps->spawned == 0)
          SpawnProcess(running_ps, 99); 
				else {
          SetProcessPriority(running_ps->pid, 99);
				}
      }
    }

    if (running_ps == NULL && h.count != 0) {
      running_ps = heap_front(&h);
      heap_pop(&h);
      if (running_ps->spawned == 0)
        pid = SpawnProcess(running_ps, 99);
      else {
        SetProcessPriority(running_ps->pid, 99);
      }
    }

    UNIT_TIME;
    if (running_ps)
      running_ps->remain--;
  }
}

void RunRR(struct Process *ps, int n) {
	int cur_ps = 0;
	int quantum_remain = kRRQuantum;

	struct Queue *head = NULL, *tail = NULL;
	for (int cur_time = 0; ; cur_time++) {
		if (head && head->ps->remain == 0) {
			wait(NULL);	
			quantum_remain = kRRQuantum;

			struct Queue *now = head;
			if (now->next) 
				head = head->next;
			else
				head = tail = NULL;		

			free(now);
			if (head == NULL && cur_ps == n)
				return;
		}

		while (cur_ps < n && ps[cur_ps].ready <= cur_time) {
			int pid = SpawnProcess(&ps[cur_ps], 1);
			struct Queue *now = (struct Queue *)calloc(1, sizeof(struct Queue));
			now->ps = &ps[cur_ps];

			if (head == NULL) {
				head = tail = now;
				SetProcessPriority(pid, 99);
			} else {
				tail->next = now;
				tail = now;
			}
			cur_ps++;
		}

		if (quantum_remain == 0) {
			SetProcessPriority(head->ps->pid, 1);
			quantum_remain = kRRQuantum;
			if (head->next) {
				struct Queue *now = head;
				head = head->next;
				tail->next = now;
				tail = now;
				tail->next = NULL;
				SetProcessPriority(head->ps->pid, 99);
			}
		}

		UNIT_TIME;
		if (head) {
			head->ps->remain--;
			quantum_remain--;
		}
	}	
}
