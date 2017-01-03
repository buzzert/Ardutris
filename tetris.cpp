#include <Arduboy.h>

#include "shapes.h"
#include "grid.h"
#include "input_handler.h"

using namespace std;

static Arduboy arduboy;

static shape_actor_t current_actor;

static Grid grid;
static InputHandler input_handler;

static unsigned long time_started;
static unsigned long last_update;

static unsigned long block_speed = 1;

tetromino_t* random_tetromino()
{
    static const unsigned int num_tetrominos = 7;
    tetromino_t *tetrominos[num_tetrominos] = {
        &SquareBlock,
        &LeftLBlock,
        &RightLBlock,
        &LongBlock,
        &MountainBlock,
        &ZBlock,
        &SBlock,
    };

    long random_idx = random(num_tetrominos);
    return tetrominos[random_idx];
}

void next_block()
{
    grid.commit_actor(current_actor);

    current_actor.position = { 5, 0 };
    current_actor.tetromino = random_tetromino();
    current_actor.rotation = 0;
}

void move_current_block_down()
{
    shape_actor_t ghost_actor(current_actor);
    ghost_actor.position.y += 1;

    if (!grid.actor_in_vert_bounds(ghost_actor) || grid.actor_collides(ghost_actor)) {
        next_block();
    } else {
        current_actor.position = ghost_actor.position;
    }
}

void button_handler(uint8_t button, bool down)
{
    shape_actor_t ghost_actor(current_actor);

    if (down && button == RIGHT_BUTTON) {
        ghost_actor.position.x += 1;
    }

    if (down && button == LEFT_BUTTON) {
        ghost_actor.position.x -= 1;
    }

    if (down && button == DOWN_BUTTON) {
        ghost_actor.position.y += 1;
    }

    if (down && button == A_BUTTON) {
        current_actor.rotation += 1;
    }

    if (grid.actor_in_horiz_bounds(ghost_actor)) {
        current_actor.position = ghost_actor.position;
    }
}

void update(unsigned long dt)
{
    input_handler.handle_input(arduboy);

    unsigned long now = millis();
    static unsigned long last_movement = 0;
    if ( (now - last_movement) > (1000 / block_speed) ) {
        // Every second, move interactive actor down by one block
        move_current_block_down();

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
    display_grid.commit_actor(current_actor);

    display_grid.draw(arduboy, 10, 0);

    arduboy.display();
}

void setup()
{
    randomSeed(analogRead(0));

    arduboy.begin();
    arduboy.setFrameRate(60);

    time_started = millis();
    last_update = time_started;

    input_handler.button_handler = button_handler;

    current_actor.position = { 5, 0 };
    current_actor.tetromino = &MountainBlock; //random_tetromino();
}

void loop()
{
    unsigned long now = millis();
    update(now - last_update);
    draw(now - last_update);
}
