#include "grid.h"

#define ROTATION_DEBUG 0

Grid::Grid()
{
    memset(_data, 0, sizeof(int) * GRID_SIZE);
}

void Grid::draw(Arduboy& adb, const unsigned at_x, const unsigned at_y)
{
    unsigned int bounds_width  = width()  * (SHAPE_BLOCK_WIDTH + SHAPE_BLOCK_PADDING) + 1;
    unsigned int bounds_height = height() * (SHAPE_BLOCK_WIDTH + SHAPE_BLOCK_PADDING) + 1;

    adb.fillRect(at_x, at_y, bounds_width, bounds_height, WHITE);

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
    adb.drawRect(at_x, at_y, bounds_width, bounds_height, WHITE);
}

void Grid::copy(Grid &other_grid)
{
    memcpy(_data, other_grid._data, sizeof(int) * GRID_SIZE);
}

void Grid::commit_actor(const shape_actor_t& actor)
{
    tetromino_t *tetromino = actor.tetromino;

    // Rotate if necessary
    int block[SHAPE_SIZE] = { 0 };
    point_t offset = tetromino->rotated_shape_data(actor.rotation, &block);
    point_t position = actor.position.offset_by(offset);

    // Blit to grid
    for (int y = 0; y < SHAPE_BOUNDS_HEIGHT; y++) {
        for (int x = 0; x < SHAPE_BOUNDS_WIDTH; x++) {
            if (AT(x, y) < 0) continue;

            if (block[AT(x, y)]) {
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

    int block[SHAPE_SIZE] = { 0 };
    point_t offset = actor.tetromino->rotated_shape_data(actor.rotation, &block);
    point_t position = actor.position.offset_by(offset);

    for (int y = 0; y < SHAPE_BOUNDS_HEIGHT; y++) {
        for (int x = 0; x < SHAPE_BOUNDS_WIDTH; x++) {
            int16_t x_pos = position.x + x;
            int16_t y_pos = position.y + y;

            if (AT(x, y) < 0) continue;

            if (block[AT(x, y)] && ( at(x_pos, y_pos) || (x_pos < 0) || (x_pos >= width()) || (y_pos >= height()) )) {
                collides = true;
                break;
            }
        }
    }

    return collides;
}

void Grid::_shift_down(unsigned int from_line)
{
    for (int y = from_line; y > 0; y--) {
        for (int x = 0; x < width(); x++) {
            int val = 0;
            if ( (y - 1) >= 0 ) {
                val = at(x, y - 1);
            }

            set(x, y, val);
        }
    }
}

unsigned int Grid::clear_lines()
{
    unsigned int lines_cleared = 0;
    for (int y = 0; y < height(); y++) {
        unsigned int line_sum = 0;
        for (int x = 0; x < width(); x++) if (at(x, y)) line_sum++;

        if (line_sum == width()) {
            _shift_down(y);
            lines_cleared++;
        }
    }

    return lines_cleared;
}
