#ifndef MATX_H
#define MATX_H

#include "vec.h"

typedef struct {
    double m[3][3];
} Mat3;

void mtxIdentity(Mat3* out);

void mtxRot(Mat3* out, const Vec3* rot);

void mtxRotZ(Mat3* out, double angle);

void mtxRotY(Mat3* out, double angle);

void mtxRotX(Mat3* out, double angle);

void mtxMulVec3(Vec3* out, const Mat3* m, const Vec3* v);

void mtxMulMat3(Mat3* out, const Mat3* m1, const Mat3* m2);

#endif