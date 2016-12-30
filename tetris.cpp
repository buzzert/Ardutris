#include <Arduboy.h>

#include "shapes.h"

#define BLACK 0
#define WHITE 1

#define SHAPE_BLOCK_WIDTH 4

using namespace std;

static Arduboy arduboy;

static unsigned int num_actors;
static shape_actor actors[100];
static shape_actor *interactive_actor = NULL;

static unsigned long time_started;
static unsigned long last_update;

static unsigned long block_speed = 1;

void draw_shape(tetromino_t *shape, int16_t x, int16_t y)
{
    int16_t x_offset = x;
    int16_t y_offset = y;

    const char *block_data = shape->shape_data;
    for (unsigned int row = 0; row < shape->rows; row++) {
        for (unsigned int col = 0; col < shape-> cols; col++) {
            if (*block_data++ != ' ') {
                arduboy.fillRect(x_offset, y_offset, SHAPE_BLOCK_WIDTH, SHAPE_BLOCK_WIDTH, BLACK);
            }

            x_offset += SHAPE_BLOCK_WIDTH;
        }

        y_offset += SHAPE_BLOCK_WIDTH;
        x_offset = x;
    }
}

void update(unsigned long dt)
{
    unsigned long now = millis();

    static unsigned long last_input_register = 0;
    bool debounced = (now - last_input_register) > 200;
    if (arduboy.pressed(LEFT_BUTTON) && debounced) {
        interactive_actor->position.x -= SHAPE_BLOCK_WIDTH;
        last_input_register = now;
    } else if (arduboy.pressed(RIGHT_BUTTON) && debounced) {
        interactive_actor->position.x += SHAPE_BLOCK_WIDTH;
        last_input_register = now;
    }

    static unsigned long last_movement = 0;
    if ( (now - last_movement) > (1000 / block_speed) ) {
        // Every second, move interactive actor down by one block
        if (interactive_actor) {
            interactive_actor->position.y += SHAPE_BLOCK_WIDTH;
        }

        last_movement = now;
    }
}

void draw(unsigned long dt)
{
    arduboy.clear();
    arduboy.fillScreen(WHITE);

    for (unsigned int i = 0; i < num_actors; i++) {
        draw_shape(actors[i].tetromino, actors[i].position.x, actors[i].position.y);
    }

    arduboy.display();
}

void setup()
{
    arduboy.begin();
    arduboy.setFrameRate(60);

    num_actors = 0;
    time_started = millis();
    last_update = time_started;

    num_actors = 1;
    actors[0].position = { 0, 0 };
    actors[0].tetromino = &LeftLBlock;

    interactive_actor = &actors[0];
}

void loop()
{
    unsigned long now = millis();
    update(now - last_update);
    draw(now - last_update);
}
