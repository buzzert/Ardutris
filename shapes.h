#ifndef SHAPES_H
#define SHAPES_H

#include "utils.h"

typedef struct {
    unsigned int width;
    unsigned int height;

    int shape_data[];

    int at(unsigned int x, unsigned int y) {
        if (x >= width) return 0;
        if (y >= height) return 0;
        
        return shape_data[y * width + x];
    }
} tetromino_t;

static tetromino_t SquareBlock = {
    .width = 2,
    .height = 2,
    .shape_data = {
        1, 1,
        1, 1
    },
};

static tetromino_t LeftLBlock = {
    .width = 2,
    .height = 3,
    .shape_data = {
        1, 0,
        1, 0,
        1, 1,
    },
};

static tetromino_t RightLBlock = {
    .width = 2,
    .height = 3,
    .shape_data = {
        0, 1,
        0, 1,
        1, 1,
    },
};

static tetromino_t LongBlock = {
    .width = 1,
    .height = 4,
    .shape_data = {
        1,
        1,
        1,
        1,
    },
};

static tetromino_t MountainBlock = {
    .width = 3,
    .height = 2,
    .shape_data = {
        0, 1, 0,
        1, 1, 1,
    },
};

static tetromino_t ZBlock = {
    .width = 3,
    .height = 2,
    .shape_data = {
        1, 1, 0,
        0, 1, 1,
    },
};

static tetromino_t SBlock = {
    .width = 3,
    .height = 2,
    .shape_data = {
        0, 1, 1,
        1, 1, 0,
    },
};

struct shape_actor_t
{
public:
    point_t      position;
    tetromino_t *tetromino;
    int          rotation = 0;

    shape_actor_t() {};
    shape_actor_t(const shape_actor_t& a)
        : position(a.position), tetromino(a.tetromino), rotation(a.rotation) {};
};

#endif
