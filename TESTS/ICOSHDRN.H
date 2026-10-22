#ifndef ICOSHDRN_H
#define ICOSHDRN_H

#include "scene.h"

scene icosahedron() {
    static const vec3 vertices[12] = {
        {-1,   1.61803398875,  0}, // 1
        { 1,   1.61803398875,  0}, // 2
        {-1,  -1.61803398875,  0}, // 3
        { 1,  -1.61803398875,  0}, // 4
        { 0,  -1,    1.61803398875}, // 5
        { 0,   1,    1.61803398875}, // 6
        { 0,  -1,   -1.61803398875}, // 7
        { 0,   1,   -1.61803398875}, // 8
        { 1.61803398875, 0,   -1}, // 9
        { 1.61803398875, 0,    1}, // 10
        {-1.61803398875, 0,   -1}, // 11
        {-1.61803398875, 0,    1}, // 12
    };

    static const face faces[20] = {
        // Faces around vertex 1
        {0, 11, 5, 0x50, {-0.57735f,  0.57735f,  0.57735f}},
        {0,  5, 1, 0x51, { 0.00000f,  0.93417f,  0.35682f}},
        {0,  1, 7, 0x52, { 0.00000f,  0.93417f, -0.35682f}},
        {0,  7, 10, 0x53, {-0.57735f,  0.57735f, -0.57735f}},
        {0, 10, 11, 0x54, {-0.93417f,  0.35682f,  0.00000f}},

        // Upper-middle faces
        {1,  5,  9, 0x40, { 0.57735f,  0.57735f,  0.57735f}},
        {5,  11, 4, 0x41, {-0.35682f,  0.00000f,  0.93417f}},
        {11, 10, 2, 0x42, {-0.93417f, -0.35682f,  0.00000f}},
        {10, 7,  6, 0x43, {-0.35682f,  0.00000f, -0.93417f}},
        {7,  1,  8, 0x44, { 0.57735f,  0.57735f, -0.57735f}},

        // Faces around vertex 4
        {3,  9, 4, 0x22, { 0.57735f, -0.57735f,  0.57735f}},
        {3,  4, 2, 0x23, { 0.00000f, -0.93417f,  0.35682f}},
        {3,  2, 6, 0x24, { 0.00000f, -0.93417f, -0.35682f}},
        {3,  6, 8, 0x25, { 0.57735f, -0.57735f, -0.57735f}},
        {3,  8, 9, 0x26, { 0.93417f, -0.35682f,  0.00000f}},

        // Lower-middle faces
        {4,  9, 5,  0x28, { 0.35682f,  0.00000f,  0.93417f}},
        {2,  4, 11, 0x29, {-0.57735f, -0.57735f,  0.57735f}},
        {6,  2, 10, 0x2A, {-0.57735f, -0.57735f, -0.57735f}},
        {8,  6,  7, 0x2B, { 0.35682f,  0.00000f, -0.93417f}},
        {9,  8,  1, 0x2C, { 0.93417f,  0.35682f,  0.00000f}},
    };

    scene sc;
    int vertex_count = sizeof(vertices) / sizeof(vertices[0]);
    int face_count = sizeof(faces) / sizeof(faces[0]);
    sc.vertices = (vec3*)vertices;
    sc.transformed_vertices = (vec3*)malloc(sizeof(vec3) * vertex_count);
    sc.faces = (face*)faces;
    sc.vertex_count = vertex_count;
    sc.face_count = face_count;
    sc.rot.x = 0.03; // Set rotation speed for x-axis
    sc.rot.y = 0.03; // Set rotation speed for y-axis
    sc.rot.z = 0.03; // Set rotation speed for z-axis
    return sc;
}

#endif // ICOSHDRN_H