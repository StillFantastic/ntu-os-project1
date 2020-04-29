all: scheduler

scheduler: scheduler.c scheduler.h utils.c utils.h policies.c policies.h
	gcc -std=c17 -o scheduler scheduler.c utils.c policies.c

clean:
	rm -rf scheduler 
