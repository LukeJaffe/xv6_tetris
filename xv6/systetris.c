//#include "defs.h" // for ticks (random seed)
#include "systetris.h"

int start_tetris = 0;

// screen buffers
static char oldbuf[SCREEN_WIDTH*SCREEN_HEIGHT];
static char buf[SCREEN_WIDTH*SCREEN_HEIGHT];
static char diffbuf[SCREEN_WIDTH*SCREEN_HEIGHT];

// tetris module variables
static well_t well = 
{ 
    .x=WELL_LEFT, 
    .y=WELL_TOP, 
    .w=WELL_WIDTH*BLOCK_WIDTH, 
    .h=WELL_HEIGHT*BLOCK_HEIGHT 
};
//static block_t blocks[BOARD_WIDTH*BOARD_HEIGHT];
static tet_t curr_tet;

// static function prototypes
static void draw_tet_i(tet_t* tet);
static void draw_tet_o(tet_t* tet);
static void draw_tet_t(tet_t* tet);
static void draw_tet_s(tet_t* tet);
static void draw_tet_z(tet_t* tet);
static void draw_tet_j(tet_t* tet);
static void draw_tet_l(tet_t* tet);

// function defs

void new_tet(int seed)
{
    curr_tet.t = seed%NUM_TET_TYPES;
    curr_tet.x = WELL_LEFT;
    curr_tet.y = WELL_TOP;
    curr_tet.r = 0;
    curr_tet.l = 0;
}

void rotate_tet()
{
    curr_tet.r = (curr_tet.r+1)%4;

    // check for collision (do kick if needed)
}

void move_tet(tet_move_t tet_move)
{
    switch (tet_move)
    {
        case TET_MOVE_LEFT:
            curr_tet.x -= BLOCK_WIDTH;
            break;
        case TET_MOVE_RIGHT:
            curr_tet.x += BLOCK_WIDTH;
            break;
        case TET_MOVE_DOWN:
            curr_tet.y += BLOCK_HEIGHT;
            break;
        case TET_MOVE_DROP:
            break;
        default:
            break;
    }
}

// only update pixels which have actually changed between ticks
// TODO: check if this does anything...
void diff_buf()
{
    int i;
    for (i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++)
    {
        if (buf[i] != oldbuf[i])
            diffbuf[i] = buf[i];
        else
            diffbuf[i] = oldbuf[i];
    }
}

char* get_buf()
{
    diff_buf();
    return (char*)diffbuf;
}

void update_screen()
{
    int i, j;

    // save the old screen buffer
    for (i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++)
        oldbuf[i] = buf[i]; 

    // clear screen to black
    for (i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++)
        buf[i] = 0; 

    // draw well
    for (i = well.x; i < well.x+well.w; i++)
        for (j = well.y; j < well.y+BLOCK_HEIGHT; j++)
            buf[SCREEN_WIDTH*j+i] = 1;
    for (i = well.x; i < well.x+well.w; i++)
        for (j = well.y+well.h-BLOCK_HEIGHT+1; j < well.y+well.h; j++)
            buf[SCREEN_WIDTH*j+i] = 1;
    for (i = well.x; i < well.x+BLOCK_WIDTH; i++)
        for (j = well.y; j < well.y+well.h; j++)
            buf[SCREEN_WIDTH*j+i] = 1;
    for (i = well.x+well.w-BLOCK_WIDTH; i < well.x+well.w; i++)
        for (j = well.y; j < well.y+well.h; j++)
            buf[SCREEN_WIDTH*j+i] = 1;

    // draw the current tet
    draw_tet(&curr_tet);
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
        case TET_TYPE_I:
            draw_tet_i(tet);
            break;
        case TET_TYPE_O:
            draw_tet_o(tet);
            break;
        case TET_TYPE_T:
            draw_tet_t(tet);
            break;
        case TET_TYPE_S:
            draw_tet_s(tet);
            break;
        case TET_TYPE_Z:
            draw_tet_z(tet);
            break;
        case TET_TYPE_J:
            draw_tet_j(tet);
            break;
        case TET_TYPE_L:
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
                draw_block(tet->x + i*BLOCK_WIDTH, tet->y + BLOCK_WIDTH, TET_COLOR_I);
            break;
        case 1:
            for (i = 0; i < 4; i++)
                draw_block(tet->x + 2*BLOCK_WIDTH, tet->y + i*BLOCK_WIDTH, TET_COLOR_I);
            break;
        case 2:
            for (i = 0; i < 4; i++)
                draw_block(tet->x + i*BLOCK_WIDTH, tet->y + 2*BLOCK_WIDTH, TET_COLOR_I);
            break;
        case 3:
            for (i = 0; i < 4; i++)
                draw_block(tet->x + BLOCK_WIDTH, tet->y + i*BLOCK_WIDTH, TET_COLOR_I);
            break;
        default:
            break;
    }
}

void draw_tet_o(tet_t* tet)
{
    draw_block(tet->x, tet->y, TET_COLOR_O);
    draw_block(tet->x + BLOCK_WIDTH, tet->y, TET_COLOR_O);
    draw_block(tet->x, tet->y + BLOCK_WIDTH, TET_COLOR_O);
    draw_block(tet->x + BLOCK_WIDTH, tet->y + BLOCK_WIDTH, TET_COLOR_O);
}

void draw_tet_t(tet_t* tet)
{
    switch (tet->r)
    {
        case 0:
            draw_block(tet->x, tet->y, TET_COLOR_T);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, TET_COLOR_T);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, TET_COLOR_T);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, TET_COLOR_T);
            break;
        case 1:
            draw_block(tet->x, tet->y, TET_COLOR_T);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, TET_COLOR_T);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, TET_COLOR_T);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, TET_COLOR_T);
            break;
        case 2:
            draw_block(tet->x, tet->y, TET_COLOR_T);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, TET_COLOR_T);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, TET_COLOR_T);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, TET_COLOR_T);
            break;
        case 3:
            draw_block(tet->x, tet->y, TET_COLOR_T);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, TET_COLOR_T);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, TET_COLOR_T);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, TET_COLOR_T);
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
            draw_block(tet->x, tet->y, TET_COLOR_S);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, TET_COLOR_S);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, TET_COLOR_S);
            draw_block(tet->x + BLOCK_WIDTH, tet->y - BLOCK_WIDTH, TET_COLOR_S);
            break;
        case 1:
            draw_block(tet->x, tet->y, TET_COLOR_S);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, TET_COLOR_S);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, TET_COLOR_S);
            draw_block(tet->x + BLOCK_WIDTH, tet->y + BLOCK_WIDTH, TET_COLOR_S);
            break;
        case 2:
            draw_block(tet->x, tet->y, TET_COLOR_S);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, TET_COLOR_S);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, TET_COLOR_S);
            draw_block(tet->x - BLOCK_WIDTH, tet->y + BLOCK_WIDTH, TET_COLOR_S);
            break;
        case 3:
            draw_block(tet->x, tet->y, TET_COLOR_S);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, TET_COLOR_S);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, TET_COLOR_S);
            draw_block(tet->x - BLOCK_WIDTH, tet->y - BLOCK_WIDTH, TET_COLOR_S);
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
            draw_block(tet->x, tet->y, TET_COLOR_Z);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, TET_COLOR_Z);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, TET_COLOR_Z);
            draw_block(tet->x - BLOCK_WIDTH, tet->y - BLOCK_WIDTH, TET_COLOR_Z);
            break;
        case 1:
            draw_block(tet->x, tet->y, TET_COLOR_Z);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, TET_COLOR_Z);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, TET_COLOR_Z);
            draw_block(tet->x + BLOCK_WIDTH, tet->y - BLOCK_WIDTH, TET_COLOR_Z);
            break;
        case 2:
            draw_block(tet->x, tet->y, TET_COLOR_Z);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, TET_COLOR_Z);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, TET_COLOR_Z);
            draw_block(tet->x + BLOCK_WIDTH, tet->y + BLOCK_WIDTH, TET_COLOR_Z);
            break;
        case 3:
            draw_block(tet->x, tet->y, TET_COLOR_Z);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, TET_COLOR_Z);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, TET_COLOR_Z);
            draw_block(tet->x - BLOCK_WIDTH, tet->y + BLOCK_WIDTH, TET_COLOR_Z);
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
            draw_block(tet->x, tet->y, TET_COLOR_J);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, TET_COLOR_J);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, TET_COLOR_J);
            draw_block(tet->x - BLOCK_WIDTH, tet->y - BLOCK_WIDTH, TET_COLOR_J);
            break;
        case 1:
            draw_block(tet->x, tet->y, TET_COLOR_J);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, TET_COLOR_J);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, TET_COLOR_J);
            draw_block(tet->x + BLOCK_WIDTH, tet->y - BLOCK_WIDTH, TET_COLOR_J);
            break;
        case 2:
            draw_block(tet->x, tet->y, TET_COLOR_J);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, TET_COLOR_J);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, TET_COLOR_J);
            draw_block(tet->x + BLOCK_WIDTH, tet->y + BLOCK_WIDTH, TET_COLOR_J);
            break;
        case 3:
            draw_block(tet->x, tet->y, TET_COLOR_J);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, TET_COLOR_J);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, TET_COLOR_J);
            draw_block(tet->x - BLOCK_WIDTH, tet->y + BLOCK_WIDTH, TET_COLOR_J);
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
            draw_block(tet->x, tet->y, TET_COLOR_L);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, TET_COLOR_L);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, TET_COLOR_L);
            draw_block(tet->x + BLOCK_WIDTH, tet->y - BLOCK_WIDTH, TET_COLOR_L);
            break;
        case 1:
            draw_block(tet->x, tet->y, TET_COLOR_L);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, TET_COLOR_L);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, TET_COLOR_L);
            draw_block(tet->x + BLOCK_WIDTH, tet->y + BLOCK_WIDTH, TET_COLOR_L);
            break;
        case 2:
            draw_block(tet->x, tet->y, TET_COLOR_L);
            draw_block(tet->x - BLOCK_WIDTH, tet->y, TET_COLOR_L);
            draw_block(tet->x + BLOCK_WIDTH, tet->y, TET_COLOR_L);
            draw_block(tet->x - BLOCK_WIDTH, tet->y + BLOCK_WIDTH, TET_COLOR_L);
            break;
        case 3:
            draw_block(tet->x, tet->y, TET_COLOR_L);
            draw_block(tet->x, tet->y + BLOCK_WIDTH, TET_COLOR_L);
            draw_block(tet->x, tet->y - BLOCK_WIDTH, TET_COLOR_L);
            draw_block(tet->x - BLOCK_WIDTH, tet->y - BLOCK_WIDTH, TET_COLOR_L);
            break;
        default:
            break;
    }
}
