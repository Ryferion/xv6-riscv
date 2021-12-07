#include "kernel/types.h"
#include "kernel/stat.h"

#include "user/user.h"
// #include "user/threadhelper.h"

int pass, max_pass, numthread;
lock_t thisLock;

void frisbee(void* arg)
{
    int each = *(int*)arg;
    int count = 0;
    while (count < max_pass)
    {
        if (pass == each)
        {
            lock_acquire(&thisLock);
            int currentLook = thisLock.passes;
            thisLock.passes = thisLock.passes + 1;

            if (thisLock.passes > thisLock.max_passes) // out of bounds
            {
                thisLock.passes = 0;
            }
            pass += 1;
            // printf("each: %d, thislock.passes: %d, max passes: %d\n", each, thisLock.passes, thisLock.max_passes);
            printf("Pass number no: %d, Thread %d is passing the token to thread %d\n", pass, currentLook, thisLock.passes);
            
            lock_release(&thisLock);
        }
        count += 1;
    }
}

int main(int argc, char *argv[])
{
    
    
    numthread = atoi(argv[1]);
    max_pass = atoi(argv[2]);

    lock_init(&thisLock, numthread);

    printf("threads to make: %d, max threads: %d\n", numthread, max_pass);
    for (int i = 0; i < max_pass; i++)
    {
        thread_create((void*)frisbee, (void*)&i);
        sleep(2);
    }
    exit(0);
}
