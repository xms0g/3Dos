#ifndef TRINGL_H
#define TRINGL_H

#include "vec3.h"

typedef struct {
    int a;
    int b;
    int c;
    unsigned char color;
    vec3 normal;
} face;

typedef struct {
    vec2 points[3];
    unsigned char color;
    double light_intensity;
    double avg_depth;
} triangle;

#endif