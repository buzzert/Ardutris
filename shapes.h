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

static tetromino_t RightLBlock = {
    .cols = 2,
    .rows = 3,
    .shape_data = " x x xx"
};

static tetromino_t LongBlock = {
    .cols = 1,
    .rows = 4,
    .shape_data = "xxxx"
};

static tetromino_t MountainBlock = {
    .cols = 3,
    .rows = 2,
    .shape_data = " x xxx"
};

static tetromino_t ZBlock = {
    .cols = 3,
    .rows = 2,
    .shape_data = "xx xxx"
};

static tetromino_t SBlock = {
    .cols = 3,
    .rows = 2,
    .shape_data = " xxxx "
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
