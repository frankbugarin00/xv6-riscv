#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
 
// PA2 Task 5: Aging scheduler experiment.
// Compare results with aging enabled and disabled.
 
#define CHILDREN 3
#define WORK 200000000
 
int
main(void)
{
  int priorities[CHILDREN] = {5, 10, 15};
  int ready[2];
  int start[2];
  int created[CHILDREN];
  int pid;
  int i;
  char signal;
  int experimentStart = uptime();
 
  // Create pipes to synchronize the children.
  if(pipe(ready) < 0 || pipe(start) < 0){
    printf("Pipe creation failed\n");
    exit(1);
  }
 
  printf("PA2 Task 5: Aging scheduler experiment\n");
 
  // Create three competing processes.
  for(i = 0; i < CHILDREN; i++){
    created[i] = uptime();
    pid = fork();
 
    if(pid < 0){
      printf("Fork failed\n");
      exit(1);
    }
 
    if(pid == 0){
      int firstRun;
      int finish;
      volatile int j;
 
      close(ready[0]);
      close(start[1]);
 
      // Set this child's base priority.
      setpriority(priorities[i]);
 
      // Tell the parent that this child is ready.
      signal = 'R';
      write(ready[1], &signal, 1);
 
      // Wait until the parent releases all children.
      if(read(start[0], &signal, 1) != 1){
        exit(1);
      }
 
      // Record the first time this child runs after release.
      firstRun = uptime();
 
      printf("PID %d priority %d started at %d ticks\n",
             getpid(), getpriority(), firstRun);
 
      // Perform CPU-intensive work.
      for(j = 0; j < WORK; j++){
      }
 
      finish = uptime();
 
      printf("PID %d priority %d finished at %d ticks\n",
             getpid(), getpriority(), finish);
 
      // Report approximate response and turnaround times.
      printf("PID %d response: %d ticks, turnaround: %d ticks\n",
             getpid(),
             firstRun - created[i],
             finish - created[i]);
 
      exit(0);
    }
  }
 
  // Parent no longer needs these pipe ends.
  close(ready[1]);
  close(start[0]);
 
  // Wait for all children to reach their starting point.
  for(i = 0; i < CHILDREN; i++){
    if(read(ready[0], &signal, 1) != 1){
      printf("Synchronization failed\n");
      exit(1);
    }
  }
 
  printf("All children ready. Starting experiment.\n");
 
  // Release the three children.
  for(i = 0; i < CHILDREN; i++){
    signal = 'G';
    write(start[1], &signal, 1);
  }
 
  close(ready[0]);
  close(start[1]);
 
  // Wait until every child finishes.
  for(i = 0; i < CHILDREN; i++){
    wait(0);
  }
 
  printf("All processes finished.\n");
  printf("Total elapsed time: %d ticks\n",
         uptime() - experimentStart);
 
  exit(0);
}
