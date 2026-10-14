#ifndef VEC_H
#define VEC_H
 
typedef struct {
    double x;
    double y;
} Vec2;

typedef struct {
    double x;
    double y;
    double z;
} Vec3;

void vecNormalize(Vec3* v);

double vecInvLen(const Vec3* v);

void vecSAdd(Vec3* v, const double scalar);

void vecZero(Vec3* v);

void vecNormal(Vec3* out, const Vec3* v0, const Vec3* v1, const Vec3* v2);

void vecWrap(Vec3* v, const double value);

void vecProject(Vec2* out, const Vec3* v, const int fov);

void vecRotx(Vec3* out, const Vec3* v, const double angle);

void vecRoty(Vec3* out, const Vec3* v, const double angle);

void vecRotz(Vec3* out, const Vec3* v, const double angle);

void vecAdd(Vec3* out, const Vec3* v0, const Vec3* v1);

void vecSub(Vec3* out, const Vec3* v0, const Vec3* v1);

double vecDot(const Vec3* v0, const Vec3* v1);

void vecCross(Vec3* out, const Vec3* v0, const Vec3* v1);

#endif