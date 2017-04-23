#ifndef GRID_H
#define GRID_H

#include <Arduboy.h>

#include "shapes.h"

#define BLACK 0
#define WHITE 1

#define SHAPE_BLOCK_PADDING 1
#define SHAPE_BLOCK_WIDTH 3

#define GRID_HEIGHT 15
#define GRID_WIDTH 10
#define GRID_SIZE (GRID_HEIGHT * GRID_WIDTH)

class Grid
{
public:
    Grid();

    int at(unsigned x, unsigned y) {
        return _data[(y * GRID_WIDTH) + x];
    };

    void set(unsigned x, unsigned y, int val) {
        _data[(y * GRID_WIDTH) + x] = val;
    }

    int width()  { return GRID_WIDTH; };
    int height() { return GRID_HEIGHT; };

    void copy(Grid &other_grid);
    void draw(Arduboy& adb, const unsigned x, const unsigned y);

    bool actor_collides(const shape_actor_t& actor);
    void commit_actor(const shape_actor_t& actor);

    /// Returns number of lines cleared
    unsigned int clear_lines();

    void reset();

private:
    int _data[GRID_SIZE];

    void _shift_down(unsigned int from_line);
};

#endif
