#ifndef VEC_H
#define VEC_H
 
typedef struct {
    double x;
    double y;
} vec2;

typedef struct {
    double x;
    double y;
    double z;
} vec3;

void vec3_normalize(vec3* v);

double vec3_inv_len(const vec3* v);

void vec3_s_add(vec3* v, const double scalar);

void vec3_zero(vec3* v);

void vec3_normal(vec3* out, const vec3* v0, const vec3* v1, const vec3* v2);

void vec3_wrap(vec3* v, const double value);

void vec3_project(vec2* out, const vec3* v, const int fov);

void vec3_rot_x(vec3* out, const vec3* v, const double angle);

void vec3_rot_y(vec3* out, const vec3* v, const double angle);

void vec3_rot_z(vec3* out, const vec3* v, const double angle);

void vec3_add(vec3* out, const vec3* v0, const vec3* v1);

void vec3_sub(vec3* out, const vec3* v0, const vec3* v1);

double vec3_dot(const vec3* v0, const vec3* v1);

void vec3_cross(vec3* out, const vec3* v0, const vec3* v1);

#endif