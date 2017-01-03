#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

template<typename T1, typename T2>
class Pair
{
public:
    Pair() {};
    Pair(const T1& first, const T2& second) : first(first), second(second) {};

    T1 first;
    T2 second;
};


typedef struct
{
    int16_t x;
    int16_t y;
} point_t;

#endif
