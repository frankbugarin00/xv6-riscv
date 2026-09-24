// This will include basic data types xv6's
#include "kernel/types.h"

// This will include the functions that the user of xv6 user programs are able to use
//  Gives us access to uptime(), printf(), and exit().
#include "user/user.h"


// main() is where the uptime program begins running for us to start uptime
int
main(int argc, char *argv[])
{
    // We made an  integer variable named ticks
    // We will use this to store the number of clock ticks
    // that have passed since xv6 started.
    int ticks;

    // This will call the existing xv6 uptime() system call.
    // uptime() will ask the kernel how many clock ticks have
    // happened  since the system started.
    // The returned number is stored in "ticks".
    ticks = uptime();

    // Print the number of clock ticks to the screen.
    // %d is replaced by the value stored in "ticks".
    printf("up %d clock ticks\n", ticks);

    // End the program successfully.
    // 0 will signify that the program finished without an error.
    exit(0);
}
