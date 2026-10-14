#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/pstat.h"
#include "user/user.h"
 
#define MAXPROCS 64
 
int
main(void)
{
  struct pstat ps[MAXPROCS];
 
  int n = getprocs(ps);
 
  if(n < 0){
    printf("getprocs failed\n");
    exit(1);
  }
 
  printf("PID\tPPID\tSTATE\tSIZE\tNAME\n");
 
  for(int i = 0; i < n; i++){
    printf("%d\t%d\t%d\t%ld\t%s\n",
           ps[i].pid,
           ps[i].ppid,
           ps[i].state,
           ps[i].size,
           ps[i].name);
  }
 
  exit(0);
}
