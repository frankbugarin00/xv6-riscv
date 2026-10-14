#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
 
int
main(void)
{
  int pid;
  int i;
  int ready[2];
  int start[2];
 
  // PA2 Task 4: Create pipes to synchronize the children.
  if(pipe(ready) < 0 || pipe(start) < 0){
    printf("Pipe creation failed\n");
    exit(1);
  }
 
  // PA2 Task 4: Create three processes.
  for(i = 0; i < 3; i++){
    pid = fork();
 
    if(pid < 0){
      printf("Fork failed\n");
      exit(1);
    }
 
    if(pid == 0){
      int priority = (i + 1) * 5;
      char signal = 'R';
 
      close(ready[0]);
      close(start[1]);
 
      // Assign priorities 5, 10, and 15.
      setpriority(priority);
 
      // Tell the parent this child is ready.
      write(ready[1], &signal, 1);
 
      // Wait until the parent releases all children.
      if(read(start[0], &signal, 1) != 1)
        exit(1);
 
      printf("Process %d: priority %d started\n",
             getpid(), getpriority());
 
      // Perform CPU-intensive work.
      volatile int j;
      for(j = 0; j < 100000000; j++){
      }
 
      printf("Process %d: priority %d finished\n",
             getpid(), getpriority());
 
      exit(0);
    }
  }
 
  // Parent waits until all children are ready.
  close(ready[1]);
  close(start[0]);
 
  char signal;
 
  for(i = 0; i < 3; i++){
    if(read(ready[0], &signal, 1) != 1){
      printf("Ready synchronization failed\n");
      exit(1);
    }
  }
 
  // Release all three children.
  for(i = 0; i < 3; i++){
    signal = 'G';
    write(start[1], &signal, 1);
  }
 
  close(ready[0]);
  close(start[1]);
 
  // Wait for all children to finish.
  for(i = 0; i < 3; i++){
    wait(0);
  }
 
  printf("Scheduler test completed\n");
  exit(0);
}
