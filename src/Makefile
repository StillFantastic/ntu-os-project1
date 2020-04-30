all: scheduler

scheduler: scheduler.c scheduler.h utils.c utils.h policies.c policies.h heap.c heap.h
	gcc -std=c11 -o scheduler scheduler.c utils.c policies.c heap.c

clean:
	rm -rf scheduler 
