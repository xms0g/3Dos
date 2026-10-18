#ifndef MATX_H
#define MATX_H

#include "vec3.h"

typedef struct {
    double m[3][3];
} mat3;

void mtx_identity(mat3* out);

void mtx_rot(mat3* out, const vec3* rot);

void mtx_rot_z(mat3* out, double angle);

void mtx_rot_y(mat3* out, double angle);

void mtx_rot_x(mat3* out, double angle);

void mtx_mul_vec3(vec3* out, const mat3* m, const vec3* v);

void mtx_mul_mat3(mat3* out, const mat3* m1, const mat3* m2);

#endif