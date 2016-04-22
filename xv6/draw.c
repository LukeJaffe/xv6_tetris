#include "types.h"
#include "user.h"

#include "mmu.h" //pte_t for int32.h
#include "int32.h"

#define SCREEN_WIDTH    (320)
#define SCREEN_HEIGHT   (200)

// buffer must be outside of function scope because of stack memory limit?
char buf[SCREEN_WIDTH][SCREEN_HEIGHT];

int
main(int argc, char** argv)
{
    int i, j;

    //if (mode(&n, &pte, &regs) < 0)
    
    // populate the screen buffer
    for (i = 0; i < SCREEN_WIDTH; i++)
        for (j = 0; j < SCREEN_HEIGHT; j++)
            buf[i][j] = 2; 
        
    uint addr;
    if((addr = drawbuf((char*)buf)) < 0)
        printf(1, "draw: fail\n");
    else
        printf(1, "addr: %d %d\n", (int)buf, (int)addr);

    for (i = 0; i < 20; i++)
    {
        //draw(i%2+1);
        //sleep(50);
    }

    exit();
}
