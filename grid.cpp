#include "grid.h"

Grid::Grid()
{
    memset(_data, 0, GRID_SIZE);
}

void Grid::draw(Arduboy& adb, const unsigned x, const unsigned y)
{
    const int16_t frame_width = 1;

    int16_t x_offset = x + frame_width;
    int16_t y_offset = y + frame_width;

    for (unsigned int row = 0; row < GRID_ROWS; row++) {
        for (unsigned int col = 0; col < GRID_COLS; col++) {
            if (at(col, row) == 1) {
                adb.fillRect(x_offset, y_offset, SHAPE_BLOCK_WIDTH, SHAPE_BLOCK_WIDTH, BLACK);
            }

            x_offset += SHAPE_BLOCK_WIDTH + SHAPE_BLOCK_PADDING;
        }

        y_offset += SHAPE_BLOCK_WIDTH + SHAPE_BLOCK_PADDING;
        x_offset = x + frame_width;
    }

    // Frame
    adb.drawRect(x, y,
        GRID_COLS * (SHAPE_BLOCK_WIDTH + SHAPE_BLOCK_PADDING) + 1,
        GRID_ROWS * (SHAPE_BLOCK_WIDTH + SHAPE_BLOCK_PADDING) + 1,
        BLACK
    );
}
