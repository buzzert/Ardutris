#include "shapes.h"

point_t tetromino_t::rotated_shape_data(const int rotation, int (*result_shape_data)[16])
{
    memcpy(result_shape_data, &shape_data, sizeof(int) * SHAPE_SIZE);

    int translated_block[SHAPE_SIZE];

    int normalized_rotation = rotation;
    if (normalized_rotation < 0) {
        normalized_rotation = 4 - -(normalized_rotation % 4);
    }

    for (int deg = 0; deg < normalized_rotation; deg++) {
        for (int y = 0; y < SHAPE_BOUNDS_HEIGHT; y++) {
            for (int x = 0; x < SHAPE_BOUNDS_WIDTH; x++) {
                int xpos = SHAPE_BOUNDS_WIDTH - 1 - y;
                int ypos = x;

                translated_block[AT(x, y)] = (*result_shape_data)[AT(xpos, ypos)];
            }
        }

        memcpy(result_shape_data, &translated_block, sizeof(int) * SHAPE_SIZE);
    }

    point_t offset = { 0,  0 };
    if (normalized_rotation >= 2) {
        // Quadrants I and IV will have space on the left
        offset.x = (SHAPE_BOUNDS_WIDTH - width);
    }

    if (normalized_rotation > 0 && normalized_rotation < 3) {
        // Quadrants III and IV will have space on top
        offset.y = (SHAPE_BOUNDS_HEIGHT - height);
    }

    return offset;
}
