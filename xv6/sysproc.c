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
    // set VGA display mode
    vga_mode();

    // set up the array of locked blocks
    init_blocks();

    // create the first tet at top of screen
    new_tet(ticks);

    // tell interrupt handler that game has started
    start_tetris = 1;

    // loop until alive is 0
    int alive = 1;
    while (alive)
    {
        // move the curr tet down one row
        int code = move_tet(TET_MOVE_DOWN);

        // nothing blocking the curr tet
        if (code == 0)
        {
            // update the display buffer
            update_screen();

            // write the display buffer to the vga
            draw_unchained();

            // wait 1 tick
            syssleep(50);
        }
        // tet locked on non-top row spawns new tet
        else if (code == 1)
        {
            new_tet(ticks);
        }
        // tet locked on top row is losing condition
        else if (code == -1)
        {
            alive = 0;
        }
    }

    // switch back to text mode
    display_text();

    // return score to user
    return get_score();
}
