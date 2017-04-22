#include "shapes.h"

void tetromino_t::rotated_shape_data(const int rotation, int (*result_shape_data)[16])
{
    const int n = 4;
    int block[16] = { 0 };
    memcpy(&block, &shape_data, sizeof(int) * 16);

    for (int deg = 0; deg < (abs(rotation) % 4); deg++) {
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
}
