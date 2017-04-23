#include "shapes.h"

point_t tetromino_t::rotated_shape_data(const int rotation, int (*result_shape_data)[16])
{
    const int n = 4;
    int block[16] = { 0 };
    memcpy(&block, &shape_data, sizeof(int) * 16);

    int block_width = width;
    int block_height = height;

    point_t offset = { 0, 0 };
    int normalized_rotation = (abs(rotation) % 4);
    for (int deg = 0; deg < normalized_rotation; deg++) {
        int translated_block[n * n];
        memset(&translated_block, 0, sizeof(int) * n * n);

        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                int xpos = n - 1 - y;
                int ypos = x;

                translated_block[4 * y + x] = block[4 * ypos + xpos];
            }
        }

        memcpy(&block, &translated_block, sizeof(int) * n * n);
    }

    memcpy(result_shape_data, &block, sizeof(int) * n * n);

    // too tired...
    const int width_offset_val = 4 - width;
    int offset_table_x[] = { 0, 0, width_offset_val, width_offset_val };

    const int height_offset_val = 4 - height;
    int offset_table_y[] = { 0, height_offset_val, height_offset_val, 0 };

    return { offset_table_x[normalized_rotation], offset_table_y[normalized_rotation] };
}
