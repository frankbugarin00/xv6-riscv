#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
 
int
main(void)
{
  int before;
  int after;
 
  before = getpriority();
  printf("Priority before: %d\n", before);
 
  setpriority(5);
 
  after = getpriority();
  printf("Priority after: %d\n", after);
 
  if(after == 5)
    printf("Priority test PASSED\n");
  else
    printf("Priority test FAILED\n");
 
  exit(0);
}
