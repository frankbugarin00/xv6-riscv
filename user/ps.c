#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

// Process states used by xv6.
#define SLEEPING 2
#define RUNNABLE 3
#define RUNNING 4
#define ZOMBIE 5
 
int
main(int argc, char **argv)
{
  // PA2 Task 1: Create an array to store process information.
  struct pstat uproc[NPROC];
  int nprocs;
  int i;
 
  // PA2 Task 3: Store the current system time.
  uint64 now;
 
  char *state;
 
  // Names for the process states.
  static char *states[] = {
    [SLEEPING] "sleeping",
    [RUNNABLE] "runnable",
    [RUNNING] "running ",
    [ZOMBIE] "zombie  "
  };
 
  // PA2 Task 1: Retrieve process information using getprocs().
  nprocs = getprocs(uproc);
 
  if (nprocs < 0)
    exit(-1);
 
  // PA2 Task 3: Get the current time in system ticks.
  now = uptime();
 
  // PA2 Task 2: Display each process's priority.
  // PA2 Task 3: Add the age column.
  printf("pid\tstate\tsize\tage\tpriority\tppid\tname\n");
 
  for (i = 0; i < nprocs; i++) {
 
    // PA2 Task 1: Find the process state.
    state = states[uproc[i].state];
 
    // PA2 Task 3: Initialize the process age.
    uint64 age = 0;
 
    // PA2 Task 3: Calculate how long the process
    // has been waiting in the RUNNABLE state.
    if (uproc[i].state == RUNNABLE) {
      if (now >= uproc[i].readytime)
        age = now - uproc[i].readytime;
    }
 
    // PA2 Task 1: Display process information.
    // PA2 Task 2: Include priority.
    // PA2 Task 3: Include process age.
    printf("%d\t%s\t%ld\t%ld\t%d\t%d\t%s\n",
      uproc[i].pid,
      state,
      uproc[i].size,
      age,
      uproc[i].priority,
      uproc[i].ppid,
      uproc[i].name);
  }
 
  exit(0);
}
