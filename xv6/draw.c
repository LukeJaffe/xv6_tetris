#include "types.h"
#include "user.h"

#include "tetris.h"

int
main(int argc, char** argv)
{
    tet_t tets[2] = 
    {
        {.x = 100, .y = 100, .r = 0, .t = TET_T},
        {.x = 200, .y = 100, .r = 0, .t = TET_Z}
    }; 

    int i, j;
    for (i = 0; i < 100; i++)
    {
        clearscreen();
        for (j = 0; j < 2; j++)
        {
            updatescreen(&tets[j]);
            tets[j].y++;
        }
        drawscreen();
        sleep(10);
    }

    exit();
}
