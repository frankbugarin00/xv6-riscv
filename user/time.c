#include "kernel/types.h"
#include "user/user.h"// Will include the xv6's basic data types.
#include "kernel/types.h"

#include "kernel/pstat.h"
// Will add have the xv6 user functions/system calls.
// We will also have to have the fork exec(), wait(), uptime(), printf(), and exit().
#include "user/user.h"
// main method will get  the command-line arguments.
// AN example: time1 sleep 10
int
main(int argc, char *argv[])
{
    // pid will store the result returned by the function fork().
    // the start_time and end_time variables will store the clock tick values
    int pid;
    int start_time;
    int end_time;
    int elapsed_time;
    int percent_cpu;
    struct rusage usage;
    // time1 will need another command to be able to run
    // If the user only types "time1", argc will be less than 2
    if(argc < 2){
        fprintf(2, "usage: time command [args...]\n");
        exit(1);
    }

    // Record the time BEFORE creating/running the child process.
    start_time = uptime();

    // Create a new child process.
    pid = fork();

    // A negative return value means fork failed.
    if(pid < 0){
        fprintf(2, "time: fork failed\n");
        exit(1);
    }

    // fork() returns 0 inside the child process.
    if(pid == 0){

        // Will replace the child process with the command the user
        // asked time1 to run
        //
        // An example would br:
        // time1 sleep 10
        //
        // argv[1] = "sleep"
        // argv[2] = "10"
        //
        // &argv[1] passes "sleep" and "10" to exec().
        exec(argv[1], &argv[1]);
 
        // exec() only returns if something went wrong.
        fprintf(2, "time: exec failed\n");
        exit(1);
    }
 
    // This is the parent process.
    // Wait here until the child command finishes.
    wait2(0, &usage);
 
    // Record the time AFTER the child has finished.
    end_time = uptime();
 
    // Subtract the starting time from the ending time
    // to calculate the total elapsed time.
    elapsed_time = end_time - start_time;
 
    if(elapsed_time > 0)
     percent_cpu = (usage.cputime * 100) / elapsed_time;
    else
     percent_cpu = 0;
 
    printf("elapsed time: %d ticks, cpu time: %d ticks, %d%% CPU\n",
       elapsed_time, usage.cputime, percent_cpu);
 
    // End time1 successfully.
    exit(0);
}
