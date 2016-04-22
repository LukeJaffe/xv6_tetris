#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "int32.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_mode(void)
{
    int* nptr;
    pte_t* pptr;
    struct regs16* rptr;

    if(argptr(0, (char**)&nptr, sizeof(int)) < 0)
        return -1;

    if(argptr(0, (char**)&pptr, sizeof(pte_t)) < 0)
        return -1;

    if(argptr(0, (char**)&rptr, sizeof(struct regs16)) < 0)
        return -1;

    pushcli();
    *pptr = biosmap();
    int32(*nptr, rptr);  
    biosunmap(*pptr);
    popcli();

    return 0;
}

int
sys_draw(void)
{
    int n;
    if(argint(0, &n) < 0)
        return -1;

    //bios_int(0x10, 0x13);
    struct regs16 regs = { .ax = 0x13};
    pushcli();
    pte_t original = biosmap();
    int32(0x10, &regs);  
    biosunmap(original);
    popcli();

    memset((char *)P2V(0xA0000), n, (320*200));
    //for(y = 0; y < 200; y++)
    //memset((char *)P2V(0xA0000) + (y*320+80), y, 80);

    //int i;
    //for(i=0;i<10000000;i++);

    //bios_int(0x10, 0x3);

    return 0;
}

int
sys_drawbuf(void)
{
    int bufaddr;

    if(argint(0, &bufaddr) < 0)
        return -1;

    struct regs16 regs = { .ax = 0x13};
    pushcli();
    pte_t original = biosmap();
    int32(0x10, &regs);  
    biosunmap(original);
    popcli();

    char* buf = (char*)bufaddr;

    memmove((char *)P2V(0xA0000), buf, (320*200));

    return (int)buf;
}
