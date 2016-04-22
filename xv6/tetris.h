#define SCREEN_WIDTH    (320)
#define SCREEN_HEIGHT   (200)

#define BOARD_WIDTH     (10)                // in blocks
#define BOARD_HEIGHT    (20)                // in blocks
#define WELL_WIDTH      (BOARD_WIDTH+2)     // in blocks
#define WELL_HEIGHT     (BOARD_HEIGHT+2)    // in blocks
#define BLOCK_WIDTH     (9)                 // in pixels
#define BLOCK_HEIGHT    (9)                 // in pixels

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

typedef struct tet
{
    int x;
    int y;
    int r;
    int t;
} tet_t;

typedef struct well
{
    int x;
    int y;
    int w;
    int h;
} well_t;
