#define SCREEN_WIDTH    (320)
#define SCREEN_HEIGHT   (200)

#define BOARD_WIDTH     (10)                // in blocks
#define BOARD_HEIGHT    (20)                // in blocks
#define WELL_WIDTH      (BOARD_WIDTH+2)     // in blocks
#define WELL_HEIGHT     (BOARD_HEIGHT+2)    // in blocks
#define BLOCK_WIDTH     (9)                 // in pixels
#define BLOCK_HEIGHT    (9)                 // in pixels

#define WELL_TOP        (0)
#define WELL_LEFT       (SCREEN_WIDTH/2-(WELL_WIDTH*BLOCK_WIDTH)/2)

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

typedef struct block
{
    int x;
    int y;
    int c;
    int p;
} block_t;

typedef struct tet
{
    int x;
    int y;
    int r;
    int t;
    int l;
} tet_t;

typedef struct well
{
    int x;
    int y;
    int w;
    int h;
} well_t;

// extern variables
extern int start_tetris;

// prototypes
char* get_buf();
void update_screen();
void new_tet(int seed);
void rotate_tet();
void move_tet(tet_move_t tet_move);
void draw_block(int x, int y, int c);
void draw_tet(struct tet* tet);
void tetris();
