#include <Arduboy.h>

#include "shapes.h"
#include "grid.h"
#include "input_handler.h"

using namespace std;

static Arduboy arduboy;

static shape_actor current_actor;

static Grid grid;
static InputHandler input_handler;

static unsigned long time_started;
static unsigned long last_update;

static unsigned long block_speed = 1;

void button_handler(uint8_t button, bool down)
{
    if (down && button == RIGHT_BUTTON) {
        current_actor.position.x += 1;
    }

    if (down && button == LEFT_BUTTON) {
        current_actor.position.x -= 1;
    }
}

void update(unsigned long dt)
{
    input_handler.handle_input(arduboy);
    
    unsigned long now = millis();
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

    Grid display_grid;
    display_grid.copy(grid);

    // Put current actor onto the display grid
    int16_t x = current_actor.position.x;
    int16_t y = current_actor.position.y;
    const char *shape_data = current_actor.tetromino->shape_data;
    for (unsigned int row = 0; row < current_actor.tetromino->rows; row++) {
        for (unsigned int col = 0; col < current_actor.tetromino->cols; col++) {
            if (*shape_data++ != ' ') {
                display_grid.set(x + col, y + row, 1);
            }
        }
    }

    display_grid.draw(arduboy, 10, 0);

    arduboy.display();
}

void setup()
{
    arduboy.begin();
    arduboy.setFrameRate(60);

    time_started = millis();
    last_update = time_started;

    input_handler.button_handler = button_handler;

    current_actor.position = { 0, 0 };
    current_actor.tetromino = &SquareBlock;
}

void loop()
{
    unsigned long now = millis();
    update(now - last_update);
    draw(now - last_update);
}
