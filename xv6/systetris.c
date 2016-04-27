//#include "defs.h" // for ticks (random seed)
#include "print.h"
#include "systetris.h"
#include "display.h"

struct tet
{
    int x;
    int y;
    int r;
    int t;
    tet_bounds_t b;
    block_t blocks[4];
} curr_tet;

int start_tetris = 0;
int score = 0;

// tetris module variables
static well_t well = 
{ 
    .x = WELL_LEFT, 
    .y = WELL_TOP, 
    .w = WELL_WIDTH*BLOCK_WIDTH, 
    .h = WELL_HEIGHT*BLOCK_HEIGHT 
};

well_bounds_t well_bounds = 
{
    .l = BOARD_LEFT,
    .r = BOARD_RIGHT,
    .t = BOARD_TOP,
    .b = BOARD_BOT
};
static block_t blocks[NUM_BLOCKS];

static void draw_block(int x, int y, int c);
static void draw_blocks();

// static function prototypes
static void set_tet_i();
static void set_tet_o();
static void set_tet_t();
static void set_tet_s();
static void set_tet_z();
static void set_tet_j();
static void set_tet_l();

/*
static void bounds_tet_i();
static void bounds_tet_o();
static void bounds_tet_t();
static void bounds_tet_s();
static void bounds_tet_z();
static void bounds_tet_j();
static void bounds_tet_l();
*/

void init_blocks()
{
    int i;
    for (i = 0; i < NUM_BLOCKS; i++)
        blocks[i].p = 0;
}

void draw_blocks()
{
    int i;
    for (i = 0; i < NUM_BLOCKS; i++)
        if (blocks[i].p)
            draw_block(blocks[i].x, blocks[i].y, blocks[i].c);
}

void set_tet()
{
    switch (curr_tet.t)
    {
        case TET_TYPE_I:
            set_tet_i();
            break;
        case TET_TYPE_O:
            set_tet_o();
            break;
        case TET_TYPE_T:
            set_tet_t();
            break;
        case TET_TYPE_S:
            set_tet_s();
            break;
        case TET_TYPE_Z:
            set_tet_z();
            break;
        case TET_TYPE_J:
            set_tet_j();
            break;
        case TET_TYPE_L:
            set_tet_l();
            break;
       default:
            break;
    }
}

void new_tet(int seed)
{
    //curr_tet.t = seed%NUM_TET_TYPES;
    curr_tet.t = TET_TYPE_I;
    curr_tet.x = BOARD_LEFT;
    curr_tet.y = BOARD_TOP;
    curr_tet.r = 0;         //rotation

    set_tet();
}

void check_tet()
{
         
}

void kick_tet()
{
    //int dx;

    //int i;
    //for (i = 0; i < 4; i++)
     
    /*
    int dx;
    dx = well_bounds.l - curr_tet.b.l;
    if (dx > 0)
       curr_tet.x += dx; 
    dx = well_bounds.r - curr_tet.b.r;
    if (dx < 0)
       curr_tet.x += dx;
    */
}

void rotate_tet()
{
    curr_tet.r = (curr_tet.r+1)%4;
    set_tet();

    // check for collision (do kick if needed)
    //kick_tet();
}

int left_bound()
{
    int i, x=10000;
    for (i = 0; i < 4; i++)
    {
        if (curr_tet.blocks[i].x < x)
            x = curr_tet.blocks[i].x;
    }
    return x;
}

int right_bound()
{
    int i, x=-1;
    for (i = 0; i < 4; i++)
    {
        if (curr_tet.blocks[i].x > x)
            x = curr_tet.blocks[i].x;
    }
    return x;
}

void move_left()
{
    int i, j;

    // check if any blocks to the left of this one
    for (i = 0; i < NUM_BLOCKS; i++)
        if (blocks[i].p)
            for (j = 0; j < 4; j++)
                if (curr_tet.blocks[j].y == blocks[i].y)
                    if (curr_tet.blocks[j].x-BLOCK_WIDTH == blocks[i].x)
                        return;

    // check if touching left well wall
    if (left_bound() > well_bounds.l)
    {
        curr_tet.x -= BLOCK_WIDTH;
        for (i = 0; i < 4; i++)
            curr_tet.blocks[i].x -= BLOCK_WIDTH;
    }
}

void move_right()
{
    int i, j;

    // check if any blocks to the right of this one
    for (i = 0; i < NUM_BLOCKS; i++)
        if (blocks[i].p)
            for (j = 0; j < 4; j++)
                if (curr_tet.blocks[j].y == blocks[i].y)
                    if (curr_tet.blocks[j].x+BLOCK_WIDTH == blocks[i].x)
                        return;

    // check if touching right well wall
    if (right_bound()+BLOCK_WIDTH < well_bounds.r)
    {
        curr_tet.x += BLOCK_WIDTH;
        for (i = 0; i < 4; i++)
            curr_tet.blocks[i].x += BLOCK_WIDTH;
    }
}

int move_down()
{
    int i, j;
    
    // check if curr tet is on top of any well blocks
    for (i = 0; i < NUM_BLOCKS; i++)
        if (blocks[i].p)
            for (j = 0; j < 4; j++)
                if (curr_tet.blocks[j].x == blocks[i].x)
                    if (curr_tet.blocks[j].y+BLOCK_HEIGHT == blocks[i].y)
                        return 0;

    // check if curr tet is on well floor
    for (i = 0; i < 4; i++)
        if (curr_tet.blocks[i].y == well_bounds.b)
            return 0;

    // if not touching any blocks or floor, then move down
    curr_tet.y += BLOCK_HEIGHT;
    for (i = 0; i < 4; i++)
        curr_tet.blocks[i].y += BLOCK_HEIGHT;
    return 1;
}

void lock_tet()
{
    int i, j;
    for (i = 0, j = 0; i < 4 && j < NUM_BLOCKS; j++)
    {
        if (blocks[j].p == 0)
        {
            blocks[j].x = curr_tet.blocks[i].x;
            blocks[j].y = curr_tet.blocks[i].y;
            blocks[j].c = curr_tet.blocks[i].c;
            blocks[j].p = 1;
            i++;
        }
    }
}

void clear_rows()
{
    int i, idx;
    int rows[NUM_ROWS];

    // init rows to all 0
    for (i = 0; i < NUM_ROWS; i++)
        rows[i] = 0;

    // how many blocks are in each row
    for (i = 0; i < NUM_BLOCKS; i++)
    {
        if (blocks[i].p)
        {
            idx = blocks[i].y/BLOCK_HEIGHT - 1;
            rows[idx]++;
        }
    }

    // mark all full rows
    for (i = 0; i < NUM_ROWS; i++)
    {
        //cprintf("row %d: %d\n", i, rows[i]);
        if (rows[i] == NUM_COLS)
            rows[i] = 1;
        else
           rows[i] = 0; 
    }

    // clear all full rows
    for (i = 0; i < NUM_BLOCKS; i++)
    {
        if (blocks[i].p)
        {
            idx = blocks[i].y/BLOCK_HEIGHT - 1;
            if (rows[idx])
                blocks[i].p = 0;
        }
    }

    // get idx of a cleared row
    int cr = 0;
    for (i = 0; i < NUM_ROWS; i++)
    {
        if (rows[i])
        {
            idx = i;
            cr++;
        }
    }

    // drop all blocks above cleared rows
    int j;
    if (cr > 0)
    {
        for (i = 0; i < NUM_BLOCKS; i++)
        {
            if (blocks[i].p)
            {
                j = blocks[i].y/BLOCK_HEIGHT - 1;
                if (j < idx)
                    blocks[i].y += cr*BLOCK_HEIGHT;
            }
        }
        score += 100*cr;
    }
}

int move_tet(tet_move_t tet_move)
{
    switch (tet_move)
    {
        case TET_MOVE_LEFT:
            move_left();
            return 0;
        case TET_MOVE_RIGHT:
            move_right();
            return 0;
        case TET_MOVE_DOWN:
            if (move_down())
            {
                return 0;
            }
            else
            {
                lock_tet();
                clear_rows();
                return 1;
            }
        case TET_MOVE_DROP:
            while (move_down());
            return 0;
        default:
            return -1;
    }
}

void update_screen()
{
    int i, j;

#if MODE_UNCHAINED
    int p;
    // clear screen to black
    for (p = 0; p < NUM_FRAMES; p++)
        for (i = 0; i < FRAME_PIX; i++)
            frame_buffer[p][i] = 0; 

    // draw well
    for (p = 0; p < NUM_FRAMES; p++) 
        for (i = well.x; i < well.x+well.w; i++)
            for (j = well.y; j < well.y+BLOCK_HEIGHT; j++)
                frame_buffer[p][((i>>2)+((j*SCREEN_WIDTH)>>2))] = 21;
    for (p = 0; p < NUM_FRAMES; p++) 
        for (i = well.x; i < well.x+well.w; i++)
            for (j = well.y+well.h-BLOCK_HEIGHT+1; j < well.y+well.h; j++)
                frame_buffer[p][((i>>2)+((j*SCREEN_WIDTH)>>2))] = 21;
    for (p = 0; p < NUM_FRAMES; p++) 
        for (i = well.x; i < well.x+BLOCK_WIDTH; i++)
            for (j = well.y; j < well.y+well.h; j++)
                frame_buffer[p][((i>>2)+((j*SCREEN_WIDTH)>>2))] = 21;
    for (p = 0; p < NUM_FRAMES; p++) 
        for (i = well.x+well.w-BLOCK_WIDTH+1; i < well.x+well.w; i++)
            for (j = well.y; j < well.y+well.h; j++)
                frame_buffer[p][((i>>2)+((j*SCREEN_WIDTH)>>2))] = 21;
#else
    // clear screen to black
    for (i = 0; i < SCREEN_PIX; i++)
        frame_buffer[i] = 0; 

    // draw well
    for (i = well.x; i < well.x+well.w; i++)
        for (j = well.y; j < well.y+BLOCK_HEIGHT; j++)
            frame_buffer[SCREEN_WIDTH*j + i] = 21;
    for (i = well.x; i < well.x+well.w; i++)
        for (j = well.y+well.h-BLOCK_HEIGHT+1; j < well.y+well.h; j++)
            frame_buffer[SCREEN_WIDTH*j + i] = 21;
    for (i = well.x; i < well.x+BLOCK_WIDTH; i++)
        for (j = well.y; j < well.y+well.h; j++)
            frame_buffer[SCREEN_WIDTH*j + i] = 21;
    for (i = well.x+well.w-BLOCK_WIDTH+1; i < well.x+well.w; i++)
        for (j = well.y; j < well.y+well.h; j++)
            frame_buffer[SCREEN_WIDTH*j + i] = 21;
#endif
    // draw the current tet
    draw_tet();

    // draw locked blocks in well
    draw_blocks();
}

void draw_block(int x, int y, int c)
{
    int i, j;
    for (i = x+1; i < x+BLOCK_WIDTH; i++)
        for (j = y+1; j < y+BLOCK_HEIGHT; j++)
            frame_buffer[SCREEN_WIDTH*j+i] = c;
}

// function defs
void bounds_tet()
{
    /*
    switch (curr_tet.t)
    {
        case TET_TYPE_I:
            bounds_tet_i();
            break;
        case TET_TYPE_O:
            bounds_tet_o();
            break;
        case TET_TYPE_T:
            bounds_tet_t();
            break;
        case TET_TYPE_S:
            bounds_tet_s();
            break;
        case TET_TYPE_Z:
            bounds_tet_z();
            break;
        case TET_TYPE_J:
            bounds_tet_j();
            break;
        case TET_TYPE_L:
            bounds_tet_l();
            break;
       default:
            break;
    }
    */
}

/*
void bounds_tet_i()
{
    switch (curr_tet.r)
    {
        case 0:
            curr_tet.b.l = curr_tet.x;
            curr_tet.b.r = curr_tet.x+4*BLOCK_WIDTH;
            curr_tet.b.t = curr_tet.y+1*BLOCK_HEIGHT;
            curr_tet.b.b = curr_tet.y+1*BLOCK_HEIGHT;
            break;
        case 1:
            curr_tet.b.l = curr_tet.x+2*BLOCK_WIDTH;
            curr_tet.b.r = curr_tet.x+3*BLOCK_WIDTH;
            curr_tet.b.t = curr_tet.y;
            curr_tet.b.b = curr_tet.y+3*BLOCK_HEIGHT;
            break;
        case 2:
            curr_tet.b.l = curr_tet.x;
            curr_tet.b.r = curr_tet.x+4*BLOCK_WIDTH;
            curr_tet.b.t = curr_tet.y+2*BLOCK_HEIGHT;
            curr_tet.b.b = curr_tet.y+2*BLOCK_HEIGHT;
            break;
        case 3:
            curr_tet.b.l = curr_tet.x+1*BLOCK_WIDTH;
            curr_tet.b.r = curr_tet.x+2*BLOCK_WIDTH;
            curr_tet.b.t = curr_tet.y;
            curr_tet.b.b = curr_tet.y+3*BLOCK_HEIGHT;
            break;
        default:
            break;
    }
}

void bounds_tet_o()
{
}

void bounds_tet_t()
{
}

void bounds_tet_s()
{
}

void bounds_tet_z()
{
}

void bounds_tet_j()
{
}

void bounds_tet_l()
{
}
*/

void draw_tet()
{
    int i;
    for (i = 0; i < 4; i++)
        draw_block(curr_tet.blocks[i].x, curr_tet.blocks[i].y, curr_tet.blocks[i].c);
    /*
    switch (tet->t)
    {
        case TET_TYPE_I:
            set_tet_i(tet);
            break;
        case TET_TYPE_O:
            set_tet_o(tet);
            break;
        case TET_TYPE_T:
            set_tet_t(tet);
            break;
        case TET_TYPE_S:
            set_tet_s(tet);
            break;
        case TET_TYPE_Z:
            set_tet_z(tet);
            break;
        case TET_TYPE_J:
            set_tet_j(tet);
            break;
        case TET_TYPE_L:
            set_tet_l(tet);
            break;
       default:
            break;
    }
    */
}

void set_tet_i()
{
    int i;
    switch (curr_tet.r)
    {
        case 0:
            for (i = 0; i < 4; i++)
            {
                //draw_block(tet->x + i*BLOCK_WIDTH, tet->y + BLOCK_WIDTH, TET_COLOR_I);
                curr_tet.blocks[i].x = curr_tet.x + i*BLOCK_WIDTH;
                curr_tet.blocks[i].y = curr_tet.y + BLOCK_WIDTH;
                curr_tet.blocks[i].c = TET_COLOR_I;
            }
            break;
        case 1:
            for (i = 0; i < 4; i++)
            {
                //draw_block(curr_tet.x + 2*BLOCK_WIDTH, curr_tet.y + i*BLOCK_WIDTH, TET_COLOR_I);
                curr_tet.blocks[i].x = curr_tet.x + 2*BLOCK_WIDTH;
                curr_tet.blocks[i].y = curr_tet.y + i*BLOCK_WIDTH;
                curr_tet.blocks[i].c = TET_COLOR_I;
            }
            break;
        case 2:
            for (i = 0; i < 4; i++)
            {
                //draw_block(curr_tet.x + i*BLOCK_WIDTH, curr_tet.y + 2*BLOCK_WIDTH, TET_COLOR_I);
                curr_tet.blocks[i].x = curr_tet.x + i*BLOCK_WIDTH;
                curr_tet.blocks[i].y = curr_tet.y + 2*BLOCK_WIDTH;
                curr_tet.blocks[i].c = TET_COLOR_I;
            }
            break;
        case 3:
            for (i = 0; i < 4; i++)
            {
                //draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y + i*BLOCK_WIDTH, TET_COLOR_I);
                curr_tet.blocks[i].x = curr_tet.x + BLOCK_WIDTH;
                curr_tet.blocks[i].y = curr_tet.y + i*BLOCK_WIDTH;
                curr_tet.blocks[i].c = TET_COLOR_I;
            }
            break;
        default:
            break;
    }
}

void set_tet_o()
{
    draw_block(curr_tet.x, curr_tet.y, TET_COLOR_O);
    draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y, TET_COLOR_O);
    draw_block(curr_tet.x, curr_tet.y + BLOCK_WIDTH, TET_COLOR_O);
    draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y + BLOCK_WIDTH, TET_COLOR_O);
}

void set_tet_t()
{
    switch (curr_tet.r)
    {
        case 0:
            draw_block(curr_tet.x, curr_tet.y, TET_COLOR_T);
            draw_block(curr_tet.x - BLOCK_WIDTH, curr_tet.y, TET_COLOR_T);
            draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y, TET_COLOR_T);
            draw_block(curr_tet.x, curr_tet.y - BLOCK_WIDTH, TET_COLOR_T);
            break;
        case 1:
            draw_block(curr_tet.x, curr_tet.y, TET_COLOR_T);
            draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y, TET_COLOR_T);
            draw_block(curr_tet.x, curr_tet.y - BLOCK_WIDTH, TET_COLOR_T);
            draw_block(curr_tet.x, curr_tet.y + BLOCK_WIDTH, TET_COLOR_T);
            break;
        case 2:
            draw_block(curr_tet.x, curr_tet.y, TET_COLOR_T);
            draw_block(curr_tet.x - BLOCK_WIDTH, curr_tet.y, TET_COLOR_T);
            draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y, TET_COLOR_T);
            draw_block(curr_tet.x, curr_tet.y + BLOCK_WIDTH, TET_COLOR_T);
            break;
        case 3:
            draw_block(curr_tet.x, curr_tet.y, TET_COLOR_T);
            draw_block(curr_tet.x - BLOCK_WIDTH, curr_tet.y, TET_COLOR_T);
            draw_block(curr_tet.x, curr_tet.y - BLOCK_WIDTH, TET_COLOR_T);
            draw_block(curr_tet.x, curr_tet.y + BLOCK_WIDTH, TET_COLOR_T);
            break;
        default:
            break;
    }
}

void set_tet_s()
{
    switch (curr_tet.r)
    {
        case 0:
            draw_block(curr_tet.x, curr_tet.y, TET_COLOR_S);
            draw_block(curr_tet.x - BLOCK_WIDTH, curr_tet.y, TET_COLOR_S);
            draw_block(curr_tet.x, curr_tet.y - BLOCK_WIDTH, TET_COLOR_S);
            draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y - BLOCK_WIDTH, TET_COLOR_S);
            break;
        case 1:
            draw_block(curr_tet.x, curr_tet.y, TET_COLOR_S);
            draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y, TET_COLOR_S);
            draw_block(curr_tet.x, curr_tet.y - BLOCK_WIDTH, TET_COLOR_S);
            draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y + BLOCK_WIDTH, TET_COLOR_S);
            break;
        case 2:
            draw_block(curr_tet.x, curr_tet.y, TET_COLOR_S);
            draw_block(curr_tet.x, curr_tet.y + BLOCK_WIDTH, TET_COLOR_S);
            draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y, TET_COLOR_S);
            draw_block(curr_tet.x - BLOCK_WIDTH, curr_tet.y + BLOCK_WIDTH, TET_COLOR_S);
            break;
        case 3:
            draw_block(curr_tet.x, curr_tet.y, TET_COLOR_S);
            draw_block(curr_tet.x - BLOCK_WIDTH, curr_tet.y, TET_COLOR_S);
            draw_block(curr_tet.x, curr_tet.y + BLOCK_WIDTH, TET_COLOR_S);
            draw_block(curr_tet.x - BLOCK_WIDTH, curr_tet.y - BLOCK_WIDTH, TET_COLOR_S);
            break;
        default:
            break;
    }
}

void set_tet_z()
{
    switch (curr_tet.r)
    {
        case 0:
            draw_block(curr_tet.x, curr_tet.y, TET_COLOR_Z);
            draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y, TET_COLOR_Z);
            draw_block(curr_tet.x, curr_tet.y - BLOCK_WIDTH, TET_COLOR_Z);
            draw_block(curr_tet.x - BLOCK_WIDTH, curr_tet.y - BLOCK_WIDTH, TET_COLOR_Z);
            break;
        case 1:
            draw_block(curr_tet.x, curr_tet.y, TET_COLOR_Z);
            draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y, TET_COLOR_Z);
            draw_block(curr_tet.x, curr_tet.y + BLOCK_WIDTH, TET_COLOR_Z);
            draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y - BLOCK_WIDTH, TET_COLOR_Z);
            break;
        case 2:
            draw_block(curr_tet.x, curr_tet.y, TET_COLOR_Z);
            draw_block(curr_tet.x, curr_tet.y + BLOCK_WIDTH, TET_COLOR_Z);
            draw_block(curr_tet.x - BLOCK_WIDTH, curr_tet.y, TET_COLOR_Z);
            draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y + BLOCK_WIDTH, TET_COLOR_Z);
            break;
        case 3:
            draw_block(curr_tet.x, curr_tet.y, TET_COLOR_Z);
            draw_block(curr_tet.x - BLOCK_WIDTH, curr_tet.y, TET_COLOR_Z);
            draw_block(curr_tet.x, curr_tet.y - BLOCK_WIDTH, TET_COLOR_Z);
            draw_block(curr_tet.x - BLOCK_WIDTH, curr_tet.y + BLOCK_WIDTH, TET_COLOR_Z);
            break;
        default:
            break;
    }
}

void set_tet_j()
{
    switch (curr_tet.r)
    {
        case 0:
            draw_block(curr_tet.x, curr_tet.y, TET_COLOR_J);
            draw_block(curr_tet.x - BLOCK_WIDTH, curr_tet.y, TET_COLOR_J);
            draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y, TET_COLOR_J);
            draw_block(curr_tet.x - BLOCK_WIDTH, curr_tet.y - BLOCK_WIDTH, TET_COLOR_J);
            break;
        case 1:
            draw_block(curr_tet.x, curr_tet.y, TET_COLOR_J);
            draw_block(curr_tet.x, curr_tet.y + BLOCK_WIDTH, TET_COLOR_J);
            draw_block(curr_tet.x, curr_tet.y - BLOCK_WIDTH, TET_COLOR_J);
            draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y - BLOCK_WIDTH, TET_COLOR_J);
            break;
        case 2:
            draw_block(curr_tet.x, curr_tet.y, TET_COLOR_J);
            draw_block(curr_tet.x - BLOCK_WIDTH, curr_tet.y, TET_COLOR_J);
            draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y, TET_COLOR_J);
            draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y + BLOCK_WIDTH, TET_COLOR_J);
            break;
        case 3:
            draw_block(curr_tet.x, curr_tet.y, TET_COLOR_J);
            draw_block(curr_tet.x, curr_tet.y + BLOCK_WIDTH, TET_COLOR_J);
            draw_block(curr_tet.x, curr_tet.y - BLOCK_WIDTH, TET_COLOR_J);
            draw_block(curr_tet.x - BLOCK_WIDTH, curr_tet.y + BLOCK_WIDTH, TET_COLOR_J);
            break;
        default:
            break;
    }
}

void set_tet_l()
{
    switch (curr_tet.r)
    {
        case 0:
            draw_block(curr_tet.x, curr_tet.y, TET_COLOR_L);
            draw_block(curr_tet.x - BLOCK_WIDTH, curr_tet.y, TET_COLOR_L);
            draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y, TET_COLOR_L);
            draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y - BLOCK_WIDTH, TET_COLOR_L);
            break;
        case 1:
            draw_block(curr_tet.x, curr_tet.y, TET_COLOR_L);
            draw_block(curr_tet.x, curr_tet.y + BLOCK_WIDTH, TET_COLOR_L);
            draw_block(curr_tet.x, curr_tet.y - BLOCK_WIDTH, TET_COLOR_L);
            draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y + BLOCK_WIDTH, TET_COLOR_L);
            break;
        case 2:
            draw_block(curr_tet.x, curr_tet.y, TET_COLOR_L);
            draw_block(curr_tet.x - BLOCK_WIDTH, curr_tet.y, TET_COLOR_L);
            draw_block(curr_tet.x + BLOCK_WIDTH, curr_tet.y, TET_COLOR_L);
            draw_block(curr_tet.x - BLOCK_WIDTH, curr_tet.y + BLOCK_WIDTH, TET_COLOR_L);
            break;
        case 3:
            draw_block(curr_tet.x, curr_tet.y, TET_COLOR_L);
            draw_block(curr_tet.x, curr_tet.y + BLOCK_WIDTH, TET_COLOR_L);
            draw_block(curr_tet.x, curr_tet.y - BLOCK_WIDTH, TET_COLOR_L);
            draw_block(curr_tet.x - BLOCK_WIDTH, curr_tet.y - BLOCK_WIDTH, TET_COLOR_L);
            break;
        default:
            break;
    }
}
