#ifndef SHAPES_H
#define SHAPES_H

#include <Arduino.h>

typedef struct {
    unsigned int cols;
    unsigned int rows;

    const char *shape_data;
} tetromino_t;

static tetromino_t SquareBlock = {
    .cols = 2,
    .rows = 2,
    .shape_data = "xxxx"
};

static tetromino_t LeftLBlock = {
    .cols = 2,
    .rows = 3,
    .shape_data = "x x xx"
};

typedef struct
{
    int16_t x;
    int16_t y;
} point_t;

struct shape_actor
{
public:
    point_t      position;
    tetromino_t *tetromino;
};

#endif
