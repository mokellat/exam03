#ifndef MICRO_PAINT_H
#define MICRO_PAINT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct canva
{
    int     width;
    int     height;
    char    background;
}   t_canva;

typedef struct shape
{
    char    type;
    float   x;
    float   y;
    float   radius;
    char    background;
}   t_shape;
#endif