#include "matx.h"
#include "math.h"

void mtx_identity(mat3* out) {
    int i, j;
    
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
            out->m[i][j] = (i == j) ? 1.0 : 0.0;
}

void mtx_rot(mat3* out, const vec3* rot) {
    mat3 temp, matx, maty, matz;
    mtx_rot_x(&matx, rot->x);
    mtx_rot_y(&maty, rot->y);
    mtx_rot_z(&matz, rot->z);
    mtx_mul_mat3(&temp, &matx, &maty);
    mtx_mul_mat3(out, &temp, &matz);
}

void mtx_rot_z(mat3* out, double angle) {
    // | c -s  0 |
    // | s  c  0 |
    // | 0  0  1 |
    double c = cos_lut(angle);
    double s = sin_lut(angle);
    
    mtx_identity(out);
    
    out->m[0][0] = c;
    out->m[0][1] = -s;
    out->m[1][0] = s;
    out->m[1][1] = c;
}

void mtx_rot_y(mat3* out, double angle) {
    // |  c  0  s |
    // |  0  1  0 |
    // | -s  0  c |
    double c = cos_lut(angle);
    double s = sin_lut(angle);
    
    mtx_identity(out);
    
    out->m[0][0] = c;
    out->m[0][2] = s;
    out->m[2][0] = -s;
    out->m[2][2] = c;
}

void mtx_rot_x(mat3* out, double angle) {
    // | 1  0  0 |
    // | 0  c -s |
    // | 0  s  c |
    double c = cos_lut(angle);
    double s = sin_lut(angle);
    
    mtx_identity(out);
    
    out->m[1][1] = c;
    out->m[1][2] = -s;
    out->m[2][1] = s;
    out->m[2][2] = c;
}

void mtx_mul_vec3(vec3* out, const mat3* m, const vec3* v) {
    out->x = m->m[0][0] * v->x + m->m[0][1] * v->y + m->m[0][2] * v->z;
    out->y = m->m[1][0] * v->x + m->m[1][1] * v->y + m->m[1][2] * v->z;
    out->z = m->m[2][0] * v->x + m->m[2][1] * v->y + m->m[2][2] * v->z;
}

void mtx_mul_mat3(mat3* out, const mat3* m1, const mat3* m2) {
    int i, j;
   
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            out->m[i][j] = m1->m[i][0] * m2->m[0][j] + m1->m[i][1] * m2->m[1][j] + m1->m[i][2] * m2->m[2][j];
        }
    }
}