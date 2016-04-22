#ifndef TETRIS_H
#define TETRIS_H

#define SCREEN_WIDTH    (320)
#define SCREEN_HEIGHT   (200)

#define BOARD_WIDTH     (10)    // in blocks
#define BOARD_HEIGHT    (20)    // in blocks
#define BLOCK_WIDTH     (9)     // in pixels
#define BLOCK_HEIGHT    (9)     // in pixels

typedef enum
{
    TET_I,
    TET_O,
    TET_T,
    TET_S,
    TET_Z,
    TET_J,
    TET_L
} tet_type_t;

typedef struct
{
    int x;
    int y;
    int r;
    int t;
} tet_t;

void draw_tet_i(char* buf, tet_t* tet);
void draw_tet_o(char* buf, tet_t* tet);
void draw_tet_t(char* buf, tet_t* tet);
void draw_tet_s(char* buf, tet_t* tet);
void draw_tet_z(char* buf, tet_t* tet);
void draw_tet_j(char* buf, tet_t* tet);
void draw_tet_l(char* buf, tet_t* tet);

void draw_block(char* buf, int x, int y, int c)
{
    int i, j;
    for (i = x+1; i < x+BLOCK_WIDTH; i++)
        for (j = y+1; j < y+BLOCK_HEIGHT; j++)
            buf[SCREEN_WIDTH*i+j] = c;
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
            {
                draw_block(buf, tet->x + i*BLOCK_WIDTH, tet->y, 2);
            }
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
    }
}

void draw_tet_o(char* buf, tet_t* tet)
{
}

void draw_tet_t(char* buf, tet_t* tet)
{
}

void draw_tet_s(char* buf, tet_t* tet)
{
}

void draw_tet_z(char* buf, tet_t* tet)
{
}

void draw_tet_j(char* buf, tet_t* tet)
{
}

void draw_tet_l(char* buf, tet_t* tet)
{
}

#endif
