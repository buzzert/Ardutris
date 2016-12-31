#ifndef GRID_H
#define GRID_H

#include <Arduboy.h>

#define BLACK 0
#define WHITE 1

#define SHAPE_BLOCK_PADDING 1
#define SHAPE_BLOCK_WIDTH 3

#define GRID_ROWS 15
#define GRID_COLS 16
#define GRID_SIZE (GRID_ROWS * GRID_COLS)

class Grid
{
public:
    Grid();

    int at(unsigned x, unsigned y) {
        return _data[(y * GRID_COLS) + x];
    };

    void set(unsigned x, unsigned y, int val) {
        _data[(y * GRID_COLS) + x] = val;
    }

    void draw(Arduboy& adb, const unsigned x, const unsigned y);

private:
    int _data[GRID_SIZE];
};

#endif
