#ifndef SCENE_H
#define SCENE_H

#include "vec3.h"

typedef struct scene {
    vec3* vertices;
    face* faces;
    vec3* transformed_vertices;
    vec3 face_vertices[3];
    vec3 rot;
    int vertex_count;
    int face_count;
} scene;

#endif // SCENE_H