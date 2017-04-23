#include "grid.h"

#define ROTATION_DEBUG 0

Grid::Grid()
{
    memset(_data, 0, sizeof(int) * GRID_SIZE);
}

void Grid::draw(Arduboy& adb, const unsigned at_x, const unsigned at_y)
{
    const int16_t frame_width = 1;

    int16_t x_offset = at_x + frame_width;
    int16_t y_offset = at_y + frame_width;

    for (unsigned int y = 0; y < height(); y++) {
        for (unsigned int x = 0; x < width(); x++) {
            if (at(x, y) == 1) {
                adb.fillRect(x_offset, y_offset, SHAPE_BLOCK_WIDTH, SHAPE_BLOCK_WIDTH, BLACK);
            }

#if ROTATION_DEBUG
            if (at(x, y) == 2) {
                adb.fillRect(x_offset + 1, y_offset + 1, SHAPE_BLOCK_WIDTH - 2, SHAPE_BLOCK_WIDTH - 2, BLACK);
            }
#endif

            x_offset += SHAPE_BLOCK_WIDTH + SHAPE_BLOCK_PADDING;
        }

        y_offset += SHAPE_BLOCK_WIDTH + SHAPE_BLOCK_PADDING;
        x_offset = at_x + frame_width;
    }

    // Frame
    adb.drawRect(at_x, at_y,
        width()  * (SHAPE_BLOCK_WIDTH + SHAPE_BLOCK_PADDING) + 1,
        height() * (SHAPE_BLOCK_WIDTH + SHAPE_BLOCK_PADDING) + 1,
        BLACK
    );
}

void Grid::copy(Grid &other_grid)
{
    memcpy(_data, other_grid._data, sizeof(int) * GRID_SIZE);
}

void Grid::commit_actor(const shape_actor_t& actor)
{
    tetromino_t *tetromino = actor.tetromino;

    int width = 4;
    int height = 4;

    // Rotate if necessary
    int block[16] = { 0 };
    point_t offset = tetromino->rotated_shape_data(actor.rotation, &block);
    point_t position = actor.position.offset_by(offset);

    // Blit to grid
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (block[4 * y + x]) {
                set(position.x + x, position.y + y, 1);
            }

#if ROTATION_DEBUG
            else {
                set(position.x + x, position.y + y, 2);
            }
#endif

        }
    }
}

bool Grid::actor_collides(const shape_actor_t& actor)
{
    bool collides = false;

    int block[16] = { 0 };
    point_t offset = actor.tetromino->rotated_shape_data(actor.rotation, &block);
    point_t position = actor.position.offset_by(offset);

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            int16_t x_pos = position.x + x;
            int16_t y_pos = position.y + y;

            if (block[4 * y + x] && (at(x_pos, y_pos) || (x_pos < 0) || (x_pos >= width()))) {
                collides = true;
                break;
            }
        }
    }

    return collides;
}

bool Grid::actor_in_vert_bounds(const shape_actor_t& actor)
{
    int actor_height = actor.tetromino->height;
    if (actor.rotation % 2) {
        actor_height = actor.tetromino->width;
    }

    if (actor.position.y + actor_height > height()) return false;

    return true;
}

bool Grid::actor_in_horiz_bounds(const shape_actor_t& actor)
{
    int actor_width = actor.tetromino->width;
    if (actor.rotation % 2) {
        actor_width = actor.tetromino->height;
    }

    int block[16] = { 0 };
    point_t offset = actor.tetromino->rotated_shape_data(actor.rotation, &block);
    point_t position = actor.position.offset_by(offset);

    if (position.x < 0) return false;
    if (position.x + actor_width > width()) return false;

    return true;
}
