#ifndef _PSTAT_H_
#define _PSTAT_H_
 
struct rusage {
  uint cputime;
};
 
// PA2 Task 1: Process information returned by getprocs().
struct pstat {
  int pid;
  int state;
  uint64 size;
  int ppid;
  char name[16];
  int priority;   // PA2 Task 2: process priority
  uint64 readytime;  // PA2 Task 3: time process became RUNNABLE
};
#endif
