#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

#include "syssleep.h"
#include "display.h"
#include "systetris.h"

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
sys_tetris(void)
{
    int alive = 1;

    init_blocks();

    new_tet(ticks);

    start_tetris = 1;
    while (alive)
    {
        // move the curr tet down one row
        if (move_tet(TET_MOVE_DOWN))
            new_tet(ticks);

        // update the display buffer
        update_screen();

        // write the display buffer to the vga
        char* buf = get_buf();
        display_vga(buf);

        // sleep
        syssleep(50);
    }
    display_text();
    return 0;
}

/*
int
sys_clearscreen(void)
{
    clear_screen();
    return 0;
}

int
sys_updatescreen(void)
{
    int tptr;
    if(argint(0, &tptr) < 0)
        return -1;

    ((tet_t*)tptr)->r = tet_r;
    draw_tet((tet_t*)tptr);
    return 0;
}

int
sys_drawscreen(void)
{
}
*/
