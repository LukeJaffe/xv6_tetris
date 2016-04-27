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
#include "systetris.h"

#include "add.h"
#include "draw.h"
#include "print.h"

#define VERTICAL_RETRACE

int set_unchained()
{
    /* turn off chain-4 mode */
    outb(SC_INDEX, MEMORY_MODE);
    outb(SC_DATA, 0x06);

    /* TODO: Insert code to clear the screen here.
     *    (the BIOS only sets every fourth byte
     *       to zero -- the rest needs to be set to
     *          zero, too) */

    /* turn off long mode */
    outb(CRTC_INDEX, UNDERLINE_LOC);
    outb(CRTC_DATA, 0x00);
    /* turn on byte mode */
    outb(CRTC_INDEX, MODE_CONTROL);
    outb(CRTC_DATA, 0xe3);

    return 0;
}   

int vga_mode()
{
    // set processor to vga mode
    struct regs16 regs = { .ax = 0x13};
    pushcli();
    pte_t original = biosmap();
    int32(0x10, &regs);  
#if MODE_UNCHAINED
    set_unchained();
#endif
    biosunmap(original);
    popcli();

    return 0;
}

int draw_unchained()
{
    static int page = 0;

    char* page_addr = (char *)P2V(0xA0000 + page*FRAME_PIX);

    // move current buffer to non-visible page
#if MODE_UNCHAINED
    int i;
    outb(SC_INDEX, MAP_MASK);
    for (i = 0; i < 4; i++)
    {
        outb(SC_DATA, 1 << i);
        memmove(page_addr, frame_buffer[i], FRAME_PIX);
    }

    short flip_addr = page*FRAME_PIX;
    // flip pages
    short high_addr = HIGH_ADDRESS | (flip_addr & 0xff00);
    short low_addr = LOW_ADDRESS  | (flip_addr << 8);
    #ifdef VERTICAL_RETRACE
    while ((inb(INPUT_STATUS_1) & DISPLAY_ENABLE));
    #endif
    outw(CRTC_INDEX, high_addr);
    outw(CRTC_INDEX, low_addr);
    #ifdef VERTICAL_RETRACE
    while (!(inb(INPUT_STATUS_1) & VRETRACE));
    #endif

    // use the other page next time
    page = (page+1)%2;
#else
    memmove(page_addr, frame_buffer, SCREEN_PIX);
#endif

    return 0;
}

int display_vga(char* buf)
{
    // set processor to vga mode
    struct regs16 regs = { .ax = 0x13};
    pushcli();
    pte_t original = biosmap();
    int32(0x10, &regs);  
    biosunmap(original);
    popcli();

    //int i;
    //for (i = 0; i < 320*200; i++)
    //    buf[i] = 1;

    // write the vga with the input buffer
    memmove((char *)P2V(0xA0000), buf, (320*200));
    //cprintf("%d + %d = %d\n", 2, 3, add(2, 3));
    //cprintf("%d\n", draw(buf, (char *)P2V(0xA0000)));

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
