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

    bool actor_in_horiz_bounds(const shape_actor_t& actor);
    bool actor_in_vert_bounds(const shape_actor_t& actor);
    bool actor_in_bounds(const shape_actor_t& actor) {
        return actor_in_horiz_bounds(actor) && actor_in_vert_bounds(actor);
    }

private:
    int _data[GRID_SIZE];
};

#endif
