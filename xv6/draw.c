#include "types.h"
#include "user.h"

#include "mmu.h" //pte_t for int32.h
#include "int32.h"

#include "tetris.h"

// buffer must be outside of function scope because of stack memory limit?
char buf[SCREEN_WIDTH*SCREEN_HEIGHT];

int
main(int argc, char** argv)
{
    int i, j;

    //if (mode(&n, &pte, &regs) < 0)
    
    // populate the screen buffer
        
    uint addr;
    if((addr = drawbuf((char*)buf)) < 0)
        printf(1, "draw: fail\n");
    else
        printf(1, "addr: %d %d\n", (int)buf, (int)addr);

    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < SCREEN_WIDTH*SCREEN_HEIGHT; j++)
            buf[j] = 0; 

        tet_t tet = {.x = i, .y = 0, .r = 0, .t = TET_I};
        //draw_block(buf, i, 0, 2);
        draw_tet(buf, &tet);

        drawbuf((char*)buf);
        //sleep(10);
    }

    exit();
}
