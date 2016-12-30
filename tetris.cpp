#include <Arduboy.h>

#include "shapes.h"

#define BLACK 0
#define WHITE 1

#define SHAPE_BLOCK_PADDING 1
#define SHAPE_BLOCK_WIDTH 3

#define GRID_ROWS 15
#define GRID_COLS 16
#define GRID_SIZE (GRID_ROWS * GRID_COLS)

using namespace std;

static Arduboy arduboy;

static shape_actor current_actor;
static bool        the_grid[GRID_SIZE];

static unsigned long time_started;
static unsigned long last_update;

static unsigned long block_speed = 1;

void draw_grid(bool grid[GRID_SIZE], int16_t x, int16_t y)
{
    const int16_t frame_width = 1;

    int16_t x_offset = x + frame_width;
    int16_t y_offset = y + frame_width;

    bool *grid_ptr = grid;
    for (unsigned int row = 0; row < GRID_ROWS; row++) {
        for (unsigned int col = 0; col < GRID_COLS; col++) {
            if (grid[(row * GRID_COLS) + col]) {
                arduboy.fillRect(x_offset, y_offset, SHAPE_BLOCK_WIDTH, SHAPE_BLOCK_WIDTH, BLACK);
            }

            x_offset += SHAPE_BLOCK_WIDTH + SHAPE_BLOCK_PADDING;
        }

        y_offset += SHAPE_BLOCK_WIDTH + SHAPE_BLOCK_PADDING;
        x_offset = x + frame_width;
    }

    // Frame
    arduboy.drawRect(x, y,
        GRID_COLS * (SHAPE_BLOCK_WIDTH + SHAPE_BLOCK_PADDING) + 1,
        GRID_ROWS * (SHAPE_BLOCK_WIDTH + SHAPE_BLOCK_PADDING) + 1,
        BLACK
    );
}

void update(unsigned long dt)
{
    unsigned long now = millis();

    static unsigned long last_input_register = 0;
    bool debounced = (now - last_input_register) > 200;
    if (arduboy.pressed(LEFT_BUTTON) && debounced) {
        current_actor.position.x -= 1;
        last_input_register = now;
    } else if (arduboy.pressed(RIGHT_BUTTON) && debounced) {
        current_actor.position.x += 1;
        last_input_register = now;
    }

    static unsigned long last_movement = 0;
    if ( (now - last_movement) > (1000 / block_speed) ) {
        // Every second, move interactive actor down by one block
        if (((current_actor.position.y + current_actor.tetromino->rows) + 1) < GRID_ROWS) {
            current_actor.position.y += 1;
        }

        last_movement = now;
    }
}

void draw(unsigned long dt)
{
    arduboy.clear();
    arduboy.fillScreen(WHITE);

    bool display_grid[GRID_SIZE];
    memcpy(&display_grid, &the_grid, GRID_SIZE);

    // Put current actor onto the display grid
    int16_t x = current_actor.position.x;
    int16_t y = current_actor.position.y;
    const char *shape_data = current_actor.tetromino->shape_data;
    for (unsigned int row = 0; row < current_actor.tetromino->rows; row++) {
        for (unsigned int col = 0; col < current_actor.tetromino->cols; col++) {
            if (*shape_data++ != ' ') {
                display_grid[((y + row) * GRID_COLS) + (x + col)] = 1;
            }
        }
    }

    draw_grid(display_grid, 10, 0);

    arduboy.display();
}

void setup()
{
    arduboy.begin();
    arduboy.setFrameRate(60);

    time_started = millis();
    last_update = time_started;

    current_actor.position = { 0, 0 };
    current_actor.tetromino = &SquareBlock;

    memset(&the_grid, 0, GRID_SIZE);
}

void loop()
{
    unsigned long now = millis();
    update(now - last_update);
    draw(now - last_update);
}
