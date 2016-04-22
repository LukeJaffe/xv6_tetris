#include "types.h"
#include "defs.h"
#include "mmu.h"
#include "int32.h"
#include "memlayout.h"

void bios_int(unsigned char intnum, unsigned char regs_ax) 
{
    struct regs16 regs;
    regs.ax = regs_ax;

    pushcli();

    pte_t original = biosmap();
    int32(intnum, &regs);  
    biosunmap(original);

    popcli();
}
