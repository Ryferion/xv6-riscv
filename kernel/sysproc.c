#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if(argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

extern int callCount;
uint64 sys_giveinfo(void) //written by ryan quach and tandy dang 
{
  int n;
  argint(0, &n);
  if (n == 2)
  {
    return callCount;
  }
  if ((n == 1) || (n == 3))
  {
    uint out = print_info(n);
    return out;
  }
  return 0;
}

uint64 sys_setticket(void) //written by ryan quach
{
  struct proc *p = myproc();
  int n;
  argint(0, &n);
  // printf("sys setting ticket to n: %d\n", n);
  setticket(p, n);
  // printf("current proc tickets: %d\n", p->ticket);
  return 0;
}

/* TD: Stride scheduling code */ // written by tandy dang
uint64 sys_sched_statistics(void) {
  sched_statistics();
  return 0;
}

uint64 sys_clone(void) {
  return 0;
}