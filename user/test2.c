#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    setticket(10);    // write your own function here 
    int i,k; 
    const int loop = 10000; // adjust this parameter depending on your system speed 
    for(i=0; i < loop; i++) 
    { 
        asm("nop");  // to prevent the compiler from optimizing the for-loop 
        for(k=0; k < loop; k++) 
        { 
           asm("nop"); 
        } 
    } 
    sched_statistics(); // your syscall 
    exit(0);
}
