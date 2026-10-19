#include "vec3.h"
#include "math.h"

void vec3_normalize(vec3* v) {
    double length = vec3_inv_len(v);
    
    v->x *= length;
    v->y *= length;
    v->z *= length;
}

double vec3_inv_len(const vec3* v) {
    return inv_sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

void vec3_s_add(vec3* v, const double scalar) {
    v->x += scalar;
    v->y += scalar;
    v->z += scalar;
}

void vec3_zero(vec3* v) {
    v->x = 0.0;
    v->y = 0.0;
    v->z = 0.0;
}

void vec3_normal(vec3* out, const vec3* v0, const vec3* v1, const vec3* v2) {
    vec3 ab, ac;
    
    vec3_sub(&ab, v1, v0);
    vec3_sub(&ac, v2, v0);
    
    vec3_cross(out, &ab, &ac);
    vec3_normalize(out);
}

void vec3_wrap(vec3* v, const double value) {
    if (v->x >= value) v->x -= value;
    if (v->y >= value) v->y -= value;
    if (v->z >= value) v->z -= value;
}

void vec3_project(vec2* out, const vec3* v, const int fov) {
    out->x = (fov * v->x) / v->z;
    out->y = (fov * v->y) / v->z;
}

void vec3_rot_x(vec3* out, const vec3* v, const double angle) {
    double cosa = cos_lut(angle);
    double sina = sin_lut(angle);

    out->x = v->x;
    out->y = v->y * cosa - v->z * sina;
    out->z = v->y * sina + v->z * cosa;
}

void vec3_rot_y(vec3* out, const vec3* v, const double angle) {
    double cosa = cos_lut(angle);
    double sina = sin_lut(angle);

    out->x = v->x * cosa - v->z * sina;
    out->y = v->y;
    out->z = v->x * sina + v->z * cosa;
}

void vec3_rot_z(vec3* out, const vec3* v, const double angle) {
    double cosa = cos_lut(angle);
    double sina = sin_lut(angle);
   
    out->x = v->x * cosa - v->y * sina;
    out->y = v->x * sina + v->y * cosa;
    out->z = v->z;
}

void vec3_add(vec3* out, const vec3* v0, const vec3* v1) {
    out->x = v0->x + v1->x;
    out->y = v0->y + v1->y;
    out->z = v0->z + v1->z;
}

void vec3_sub(vec3* out, const vec3* v0, const vec3* v1) {
    out->x = v0->x - v1->x;
    out->y = v0->y - v1->y;
    out->z = v0->z - v1->z;
}

double vec3_dot(const vec3* v0, const vec3* v1) {
    return v0->x * v1->x + v0->y * v1->y + v0->z * v1->z;
}

void vec3_cross(vec3* out, const vec3* v0, const vec3* v1) {
    out->x = v0->y * v1->z - v0->z * v1->y;
    out->y = v0->z * v1->x - v0->x * v1->z;
    out->z = v0->x * v1->y - v0->y * v1->x;
}