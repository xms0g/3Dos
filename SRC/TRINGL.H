#ifndef TRINGL_H
#define TRINGL_H

#include "vec.h"

typedef struct {
    int a;
    int b;
    int c;
    unsigned char color;
    Vec3 normal;
} Face;

typedef struct {
    Vec2 points[3];
    unsigned char color;
    double lightIntensity;
    double avgDepth;
} Triangle;

#endif