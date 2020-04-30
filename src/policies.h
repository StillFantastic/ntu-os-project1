#ifndef POLICIES_H_
#define POLICIES_H_

#include "scheduler.h"
#include "utils.h"

#define kRRQuantum 500

void RunFIFO(struct Process *ps, int n);
void RunSJF(struct Process *ps, int n);
void RunPSJF(struct Process *ps, int n);
void RunRR(struct Process *ps, int n);

struct Queue {
	struct Process *ps;
	struct Queue *next;
};

#endif
