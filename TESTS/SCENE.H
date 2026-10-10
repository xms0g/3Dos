#ifndef SCENE_H
#define SCENE_H

#include "vec.h"

typedef struct Scene {
    Vec3* vertices;
    Face* faces;
    Vec3* transformedVertices;
    Vec3 faceVertices[3];
    Vec3 rot;
    int vertexCount;
    int faceCount;
} Scene;

#endif // SCENE_H