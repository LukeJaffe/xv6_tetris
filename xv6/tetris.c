#include "tetris.h"

static char buf[SCREEN_WIDTH*SCREEN_HEIGHT];

static well_t well = { .x=0, .y=0, .w=WELL_WIDTH*BLOCK_WIDTH, .h=WELL_HEIGHT*BLOCK_HEIGHT };

static void draw_tet_i(tet_t* tet);
static void draw_tet_o(tet_t* tet);
static void draw_tet_t(tet_t* tet);
static void draw_tet_s(tet_t* tet);
static void draw_tet_z(tet_t* tet);
static void draw_tet_j(tet_t* tet);
static void draw_tet_l(tet_t* tet);

char* get_buf()
{
    return (char*)buf;
}

void clear_screen()
{
    int i, j;

    // clear screen to black
    for (i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++)
        buf[i] = 0; 

    // draw well
    for (i = well.x; i < well.x+well.w; i++)
        for (j = well.y; j < well.y+BLOCK_HEIGHT; j++)
            buf[SCREEN_WIDTH*j+i] = 1;
    for (i = well.x; i < well.x+well.w; i++)
        for (j = well.y+well.h-BLOCK_HEIGHT; j < well.y+well.h; j++)
            buf[SCREEN_WIDTH*j+i] = 1;
    for (i = well.x; i < well.x+BLOCK_WIDTH; i++)
        for (j = well.y; j < well.y+well.h; j++)
            buf[SCREEN_WIDTH*j+i] = 1;
    for (i = well.x+well.w-BLOCK_WIDTH; i < well.x+well.w; i++)
        for (j = well.y; j < well.y+well.h; j++)
            buf[SCREEN_WIDTH*j+i] = 1;
}

void tetris()
{
}

void draw_block(int x, int y, int c)
{
    int i, j;
    for (i = x+1; i < x+BLOCK_WIDTH; i++)
        for (j = y+1; j < y+BLOCK_HEIGHT; j++)
            buf[SCREEN_WIDTH*j+i] = c;
}

void draw_tet(tet_t* tet)
{
    switch (tet->t)
    {
        case TET_I:
            draw_tet_i(tet);
            break;
        case TET_O:
            draw_tet_o(tet);
            break;
        case TET_T:
            draw_tet_t(tet);
            break;
        case TET_S:
            draw_tet_s(tet);
            break;
        case TET_Z:
            draw_tet_z(tet);
            break;
        case TET_J:
            draw_tet_j(tet);
            break;
        case TET_L:
            draw_tet_l(tet);
            break;
       default:
            break;
    }
}

void draw_tet_i(tet_t* tet)
{
    int i;
    switch (tet->r)
    {
        case 0:
            for (i = 0; i < 4; i++)
                draw_block(tet->x + i*BLOCK_WIDTH, tet->y + BLOCK_WIDTH, 2);
            break;
        case 1:
            for (i = 0; i < 4; i++)
                draw_block(tet->x + 2*BLOCK_WIDTH, tet->y + i*BLOCK_WIDTH, 2);
            break;
        case 2:
            for (i = 0; i < 4; i++)
                draw_block(tet->x + i*BLOCK_WIDTH, tet->y + 2*BLOCK_WIDTH, 2);
            break;
        case 3:
            for (i = 0; i < 4; i++)
                draw_block(tet->x + BLOCK_WIDTH, tet->y + i*BLOCK_WIDTH, 2);
            break;
        default:
            break;
    }
}

void draw_tet_o(tet_t* tet)
{
    draw_block(tet->x, tet->y, 2);
    draw_block(tet->x + BLOCK_WIDTH, tet->y, 2);
    draw_block(tet->x, tet->y + BLOCK_WIDTH, 2);
    draw_block(tet->x + BLOCK_WIDTH, tet->y + BLOCK_WIDTH, 2);
}

void draw_tet_t(tet_t* tet)
{
    switch (tet->r)
    {
        case 0:
            draw_block(tet->x, tet->y, 2);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, 2);
            break;
        case 1:
            draw_block(tet->x, tet->y, 2);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, 2);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, 2);
            break;
        case 2:
            draw_block(tet->x, tet->y, 2);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, 2);
            break;
        case 3:
            draw_block(tet->x, tet->y, 2);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, 2);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, 2);
            break;
        default:
            break;
    }
}

void draw_tet_s(tet_t* tet)
{
    switch (tet->r)
    {
        case 0:
            draw_block(tet->x, tet->y, 2);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, 2);
            draw_block(tet->x + BLOCK_WIDTH, tet->y - BLOCK_WIDTH, 2);
            break;
        case 1:
            draw_block(tet->x, tet->y, 2);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, 2);
            draw_block(tet->x + BLOCK_WIDTH, tet->y + BLOCK_WIDTH, 2);
            break;
        case 2:
            draw_block(tet->x, tet->y, 2);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, 2);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x - BLOCK_WIDTH, tet->y + BLOCK_WIDTH, 2);
            break;
        case 3:
            draw_block(tet->x, tet->y, 2);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, 2);
            draw_block(tet->x - BLOCK_WIDTH, tet->y - BLOCK_WIDTH, 2);
            break;
        default:
            break;
    }
}

void draw_tet_z(tet_t* tet)
{
    switch (tet->r)
    {
        case 0:
            draw_block(tet->x, tet->y, 2);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, 2);
            draw_block(tet->x - BLOCK_WIDTH, tet->y - BLOCK_WIDTH, 2);
            break;
        case 1:
            draw_block(tet->x, tet->y, 2);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, 2);
            draw_block(tet->x + BLOCK_WIDTH, tet->y - BLOCK_WIDTH, 2);
            break;
        case 2:
            draw_block(tet->x, tet->y, 2);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, 2);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x + BLOCK_WIDTH, tet->y + BLOCK_WIDTH, 2);
            break;
        case 3:
            draw_block(tet->x, tet->y, 2);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, 2);
            draw_block(tet->x - BLOCK_WIDTH, tet->y + BLOCK_WIDTH, 2);
            break;
        default:
            break;
    }
}

void draw_tet_j(tet_t* tet)
{
    switch (tet->r)
    {
        case 0:
            draw_block(tet->x, tet->y, 2);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x - BLOCK_WIDTH, tet->y - BLOCK_WIDTH, 2);
            break;
        case 1:
            draw_block(tet->x, tet->y, 2);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, 2);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, 2);
            draw_block(tet->x + BLOCK_WIDTH, tet->y - BLOCK_WIDTH, 2);
            break;
        case 2:
            draw_block(tet->x, tet->y, 2);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x + BLOCK_WIDTH, tet->y + BLOCK_WIDTH, 2);
            break;
        case 3:
            draw_block(tet->x, tet->y, 2);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, 2);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, 2);
            draw_block(tet->x - BLOCK_WIDTH, tet->y + BLOCK_WIDTH, 2);
            break;
        default:
            break;
    }
}

void draw_tet_l(tet_t* tet)
{
    switch (tet->r)
    {
        case 0:
            draw_block(tet->x, tet->y, 2);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x + BLOCK_WIDTH, tet->y - BLOCK_WIDTH, 2);
            break;
        case 1:
            draw_block(tet->x, tet->y, 2);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, 2);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, 2);
            draw_block(tet->x + BLOCK_WIDTH, tet->y + BLOCK_WIDTH, 2);
            break;
        case 2:
            draw_block(tet->x, tet->y, 2);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(tet->x - BLOCK_WIDTH, tet->y + BLOCK_WIDTH, 2);
            break;
        case 3:
            draw_block(tet->x, tet->y, 2);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, 2);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, 2);
            draw_block(tet->x - BLOCK_WIDTH, tet->y - BLOCK_WIDTH, 2);
            break;
        default:
            break;
    }
}
