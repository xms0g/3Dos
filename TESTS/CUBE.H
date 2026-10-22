#ifndef CUBE_H
#define CUBE_H

#include "mesh.h"

mesh cube() {
    static const vec3 vertices[8] = {
        {-1, -1, -1},
        {-1,  1, -1},
        { 1,  1, -1},
        { 1, -1, -1},
        { 1,  1,  1},
        { 1, -1,  1},
        {-1,  1,  1},
        {-1, -1,  1},
    };

    static const face faces[12] = {
        // front
        {0, 1, 2, 0x50, {0, 0, -1}},
        {0, 2, 3, 0x51, {0, 0, -1}},
        // right
        {3, 2, 4, 0x40, {1, 0, 0}},
        {3, 4, 5, 0x41, {1, 0, 0}},
        // back
        {5, 4, 6, 0x22, {0, 0, 1}},
        {5, 6, 7, 0x23, {0, 0, 1}},
        // left
        {7, 6, 1, 0x2A, {-1, 0, 0}},
        {7, 1, 0, 0x2B, {-1, 0, 0}},
        // top
        {1, 6, 4, 0x28, {0, 1, 0}},
        {1, 4, 2, 0x29, {0, 1, 0}},
        // bottom
        {5, 7, 0, 0x36, {0, -1, 0}},
        {5, 0, 3, 0x37, {0, -1, 0}},
    };

    mesh m;
    int vertex_count = sizeof(vertices) / sizeof(vertices[0]);
    int face_count = sizeof(faces) / sizeof(faces[0]);
    m.vertices = (vec3*)vertices;
    m.transformed_vertices = (vec3*)malloc(sizeof(vec3) * vertex_count);
    m.faces = (face*)faces;
    m.vertex_count = vertex_count;
    m.face_count = face_count;
    m.rotation.x = 0.03; // Set rotation speed for x-axis
    m.rotation.y = 0.03; // Set rotation speed for y-axis
    m.rotation.z = 0.03; // Set rotation speed for z-axis
    return m;
}

#endif