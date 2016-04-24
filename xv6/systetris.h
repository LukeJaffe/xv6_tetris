#define SCREEN_WIDTH    (320)
#define SCREEN_HEIGHT   (200)

#define BOARD_WIDTH     (10)                // in blocks
#define BOARD_HEIGHT    (20)                // in blocks
#define WELL_WIDTH      (BOARD_WIDTH+2)     // in blocks
#define WELL_HEIGHT     (BOARD_HEIGHT+2)    // in blocks
#define BLOCK_WIDTH     (9)                 // in pixels
#define BLOCK_HEIGHT    (9)                 // in pixels

// well bounds
#define WELL_TOP        (0)
#define WELL_BOT        (WELL_HEIGHT*BLOCK_HEIGHT)
#define WELL_LEFT       (SCREEN_WIDTH/2-(WELL_WIDTH*BLOCK_WIDTH)/2)
#define WELL_RIGHT      (SCREEN_WIDTH/2+(WELL_WIDTH*BLOCK_WIDTH)/2)

// board bounds
#define BOARD_TOP       (BLOCK_HEIGHT)
#define BOARD_BOT       (BOARD_HEIGHT*BLOCK_HEIGHT)
#define BOARD_LEFT      (SCREEN_WIDTH/2-(BOARD_WIDTH*BLOCK_WIDTH)/2)
#define BOARD_RIGHT     (SCREEN_WIDTH/2+(BOARD_WIDTH*BLOCK_WIDTH)/2)

// block stuff
#define NUM_BLOCKS      (BOARD_WIDTH*BOARD_HEIGHT)

typedef enum
{
    TET_TYPE_I,
    TET_TYPE_O,
    TET_TYPE_T,
    TET_TYPE_S,
    TET_TYPE_Z,
    TET_TYPE_J,
    TET_TYPE_L,
    NUM_TET_TYPES
} tet_type_t;

typedef enum
{
    TET_COLOR_I = 11,
    TET_COLOR_O = 44,
    TET_COLOR_T = 34,
    TET_COLOR_S = 47,
    TET_COLOR_Z = 40,
    TET_COLOR_J = 2,
    TET_COLOR_L = 42,
    NUM_TET_COLORS
} tet_color_t;

typedef enum
{
    TET_MOVE_LEFT,
    TET_MOVE_RIGHT,
    TET_MOVE_DOWN,
    TET_MOVE_DROP
} tet_move_t;

typedef struct tet_bounds
{
    int l;
    int r;
    int t;
    int b;
} tet_bounds_t;

typedef struct block
{
    int x;
    int y;
    int c;
    int p;
} block_t;

typedef struct well
{
    int x;
    int y;
    int w;
    int h;
} well_t;

typedef tet_bounds_t well_bounds_t;

// extern variables
extern int start_tetris;

// prototypes
char* get_buf();
void update_screen();
void new_tet(int seed);
void rotate_tet();
int move_tet(tet_move_t tet_move);
void bounds_tet();
void draw_tet();
void init_blocks();
