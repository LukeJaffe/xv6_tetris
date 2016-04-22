#include "tetris.h"

static void draw_tet_i(char* buf, tet_t* tet);
static void draw_tet_o(char* buf, tet_t* tet);
static void draw_tet_t(char* buf, tet_t* tet);
static void draw_tet_s(char* buf, tet_t* tet);
static void draw_tet_z(char* buf, tet_t* tet);
static void draw_tet_j(char* buf, tet_t* tet);
static void draw_tet_l(char* buf, tet_t* tet);

void tetris()
{
}

void draw_block(char* buf, int x, int y, int c)
{
    int i, j;
    for (i = x+1; i < x+BLOCK_WIDTH; i++)
        for (j = y+1; j < y+BLOCK_HEIGHT; j++)
            buf[SCREEN_WIDTH*j+i] = c;
}

void draw_tet(char* buf, tet_t* tet)
{
    switch (tet->t)
    {
        case TET_I:
            draw_tet_i(buf, tet);
            break;
        case TET_O:
            draw_tet_o(buf, tet);
            break;
        case TET_T:
            draw_tet_t(buf, tet);
            break;
        case TET_S:
            draw_tet_s(buf, tet);
            break;
        case TET_Z:
            draw_tet_z(buf, tet);
            break;
        case TET_J:
            draw_tet_j(buf, tet);
            break;
        case TET_L:
            draw_tet_l(buf, tet);
            break;
       default:
            break;
    }
}

void draw_tet_i(char* buf, tet_t* tet)
{
    int i;
    switch (tet->r)
    {
        case 0:
            for (i = 0; i < 4; i++)
                draw_block(buf, tet->x + i*BLOCK_WIDTH, tet->y + BLOCK_WIDTH, 2);
            break;
        case 1:
            for (i = 0; i < 4; i++)
                draw_block(buf, tet->x + 2*BLOCK_WIDTH, tet->y + i*BLOCK_WIDTH, 2);
            break;
        case 2:
            for (i = 0; i < 4; i++)
                draw_block(buf, tet->x + i*BLOCK_WIDTH, tet->y + 2*BLOCK_WIDTH, 2);
            break;
        case 3:
            for (i = 0; i < 4; i++)
                draw_block(buf, tet->x + BLOCK_WIDTH, tet->y + i*BLOCK_WIDTH, 2);
            break;
        default:
            break;
    }
}

void draw_tet_o(char* buf, tet_t* tet)
{
    draw_block(buf, tet->x, tet->y, 2);
    draw_block(buf, tet->x + BLOCK_WIDTH, tet->y, 2);
    draw_block(buf, tet->x, tet->y + BLOCK_WIDTH, 2);
    draw_block(buf, tet->x + BLOCK_WIDTH, tet->y + BLOCK_WIDTH, 2);
}

void draw_tet_t(char* buf, tet_t* tet)
{
    switch (tet->r)
    {
        case 0:
            draw_block(buf, tet->x, tet->y, 2);
            draw_block(buf, tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x, tet->y - BLOCK_WIDTH, 2);
            break;
        case 1:
            draw_block(buf, tet->x, tet->y, 2);
            draw_block(buf, tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x, tet->y - BLOCK_WIDTH, 2);
            draw_block(buf, tet->x, tet->y + BLOCK_WIDTH, 2);
            break;
        case 2:
            draw_block(buf, tet->x, tet->y, 2);
            draw_block(buf, tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x, tet->y + BLOCK_WIDTH, 2);
            break;
        case 3:
            draw_block(buf, tet->x, tet->y, 2);
            draw_block(buf, tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x, tet->y - BLOCK_WIDTH, 2);
            draw_block(buf, tet->x, tet->y + BLOCK_WIDTH, 2);
            break;
        default:
            break;
    }
}

void draw_tet_s(char* buf, tet_t* tet)
{
    switch (tet->r)
    {
        case 0:
            draw_block(buf, tet->x, tet->y, 2);
            draw_block(buf, tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x, tet->y - BLOCK_WIDTH, 2);
            draw_block(buf, tet->x + BLOCK_WIDTH, tet->y - BLOCK_WIDTH, 2);
            break;
        case 1:
            draw_block(buf, tet->x, tet->y, 2);
            draw_block(buf, tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x, tet->y - BLOCK_WIDTH, 2);
            draw_block(buf, tet->x + BLOCK_WIDTH, tet->y + BLOCK_WIDTH, 2);
            break;
        case 2:
            draw_block(buf, tet->x, tet->y, 2);
            draw_block(buf, tet->x, tet->y + BLOCK_WIDTH, 2);
            draw_block(buf, tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x - BLOCK_WIDTH, tet->y + BLOCK_WIDTH, 2);
            break;
        case 3:
            draw_block(buf, tet->x, tet->y, 2);
            draw_block(buf, tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x, tet->y + BLOCK_WIDTH, 2);
            draw_block(buf, tet->x - BLOCK_WIDTH, tet->y - BLOCK_WIDTH, 2);
            break;
        default:
            break;
    }
}

void draw_tet_z(char* buf, tet_t* tet)
{
    switch (tet->r)
    {
        case 0:
            draw_block(buf, tet->x, tet->y, 2);
            draw_block(buf, tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x, tet->y - BLOCK_WIDTH, 2);
            draw_block(buf, tet->x - BLOCK_WIDTH, tet->y - BLOCK_WIDTH, 2);
            break;
        case 1:
            draw_block(buf, tet->x, tet->y, 2);
            draw_block(buf, tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x, tet->y + BLOCK_WIDTH, 2);
            draw_block(buf, tet->x + BLOCK_WIDTH, tet->y - BLOCK_WIDTH, 2);
            break;
        case 2:
            draw_block(buf, tet->x, tet->y, 2);
            draw_block(buf, tet->x, tet->y + BLOCK_WIDTH, 2);
            draw_block(buf, tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x + BLOCK_WIDTH, tet->y + BLOCK_WIDTH, 2);
            break;
        case 3:
            draw_block(buf, tet->x, tet->y, 2);
            draw_block(buf, tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x, tet->y - BLOCK_WIDTH, 2);
            draw_block(buf, tet->x - BLOCK_WIDTH, tet->y + BLOCK_WIDTH, 2);
            break;
        default:
            break;
    }
}

void draw_tet_j(char* buf, tet_t* tet)
{
    switch (tet->r)
    {
        case 0:
            draw_block(buf, tet->x, tet->y, 2);
            draw_block(buf, tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x - BLOCK_WIDTH, tet->y - BLOCK_WIDTH, 2);
            break;
        case 1:
            draw_block(buf, tet->x, tet->y, 2);
            draw_block(buf, tet->x, tet->y + BLOCK_WIDTH, 2);
            draw_block(buf, tet->x, tet->y - BLOCK_WIDTH, 2);
            draw_block(buf, tet->x + BLOCK_WIDTH, tet->y - BLOCK_WIDTH, 2);
            break;
        case 2:
            draw_block(buf, tet->x, tet->y, 2);
            draw_block(buf, tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x + BLOCK_WIDTH, tet->y + BLOCK_WIDTH, 2);
            break;
        case 3:
            draw_block(buf, tet->x, tet->y, 2);
            draw_block(buf, tet->x, tet->y + BLOCK_WIDTH, 2);
            draw_block(buf, tet->x, tet->y - BLOCK_WIDTH, 2);
            draw_block(buf, tet->x - BLOCK_WIDTH, tet->y + BLOCK_WIDTH, 2);
            break;
        default:
            break;
    }
}

void draw_tet_l(char* buf, tet_t* tet)
{
    switch (tet->r)
    {
        case 0:
            draw_block(buf, tet->x, tet->y, 2);
            draw_block(buf, tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x + BLOCK_WIDTH, tet->y - BLOCK_WIDTH, 2);
            break;
        case 1:
            draw_block(buf, tet->x, tet->y, 2);
            draw_block(buf, tet->x, tet->y + BLOCK_WIDTH, 2);
            draw_block(buf, tet->x, tet->y - BLOCK_WIDTH, 2);
            draw_block(buf, tet->x + BLOCK_WIDTH, tet->y + BLOCK_WIDTH, 2);
            break;
        case 2:
            draw_block(buf, tet->x, tet->y, 2);
            draw_block(buf, tet->x - BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x + BLOCK_WIDTH, tet->y, 2);
            draw_block(buf, tet->x - BLOCK_WIDTH, tet->y + BLOCK_WIDTH, 2);
            break;
        case 3:
            draw_block(buf, tet->x, tet->y, 2);
            draw_block(buf, tet->x, tet->y + BLOCK_WIDTH, 2);
            draw_block(buf, tet->x, tet->y - BLOCK_WIDTH, 2);
            draw_block(buf, tet->x - BLOCK_WIDTH, tet->y - BLOCK_WIDTH, 2);
            break;
        default:
            break;
    }
}
