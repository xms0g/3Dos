#ifndef MESH_H
#define MESH_H

#include "vec3.h"

typedef struct {
    vec3* vertices;
    face* faces;
    vec3* transformed_vertices;
    vec3 rotation;
    int vertex_count;
    int face_count;
} mesh;

#endif