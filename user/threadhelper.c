#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void lock_init(struct lock_t *lck, int max_passes)
{
    lck->locked = 0;
    lck->passes = 0;
    lck->max_passes = max_passes - 1;
}

void lock_acquire(struct lock_t *lck)
{
    while(__sync_lock_test_and_set(&lck->locked, 1) != 0);
    __sync_synchronize();
}

void lock_release(struct lock_t *lck)
{
    __sync_synchronize();
    __sync_lock_release(&lck->locked);
}

int thread_create(void (*start_routine) (void*), void *arg)
{
    int pagesize = 4096;
    void *alloc_mem;
    alloc_mem = malloc(pagesize * 2);
    void *stack;

    if ((uint64)alloc_mem % pagesize == 0)
    {
        stack = alloc_mem;
    }
    else
    {
        stack = alloc_mem + (pagesize - ((uint64)alloc_mem % pagesize));
    }
    
    int thread_num;

    thread_num = clone((void*) stack, pagesize);
    if (thread_num != 0)
    {
        return thread_num;
    }

    start_routine(arg);
    free(alloc_mem);

    return thread_num;
}