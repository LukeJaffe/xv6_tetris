#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "int32.h"

#include "display.h"

int display_vga(char* buf)
{
    // set processor to vga mode
    struct regs16 regs = { .ax = 0x13};
    pushcli();
    pte_t original = biosmap();
    int32(0x10, &regs);  
    biosunmap(original);
    popcli();

    // write the vga with the input buffer
    memmove((char *)P2V(0xA0000), buf, (320*200));

    return 0;
}

int display_text()
{
    // set processor to text mode
    struct regs16 regs = { .ax = 0x03};
    pushcli();
    pte_t original = biosmap();
    int32(0x10, &regs);  
    biosunmap(original);
    popcli();

    return 0;
}
