#ifndef ICOSHDRN_H
#define ICOSHDRN_H

#include "scene.h"

Scene icosahedron() {
    static const Vec3 vertices[12] = {
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

    static const Face faces[20] = {
        // Faces around vertex 1
        {1, 12, 6, 0x50, {-0.57735f,  0.57735f,  0.57735f}},
        {1,  6, 2, 0x51, { 0.00000f,  0.93417f,  0.35682f}},
        {1,  2, 8, 0x52, { 0.00000f,  0.93417f, -0.35682f}},
        {1,  8, 11, 0x53, {-0.57735f,  0.57735f, -0.57735f}},
        {1, 11, 12, 0x54, {-0.93417f,  0.35682f,  0.00000f}},

        // Upper-middle faces
        {2,  6, 10, 0x40, { 0.57735f,  0.57735f,  0.57735f}},
        {6, 12, 5, 0x41, {-0.35682f,  0.00000f,  0.93417f}},
        {12, 11, 3, 0x42, {-0.93417f, -0.35682f,  0.00000f}},
        {11, 8, 7, 0x43, {-0.35682f,  0.00000f, -0.93417f}},
        {8,  2, 9, 0x44, { 0.57735f,  0.57735f, -0.57735f}},

        // Faces around vertex 4
        {4, 10, 5, 0x22, { 0.57735f, -0.57735f,  0.57735f}},
        {4,  5, 3, 0x23, { 0.00000f, -0.93417f,  0.35682f}},
        {4,  3, 7, 0x24, { 0.00000f, -0.93417f, -0.35682f}},
        {4,  7, 9, 0x25, { 0.57735f, -0.57735f, -0.57735f}},
        {4,  9, 10, 0x26, { 0.93417f, -0.35682f,  0.00000f}},

        // Lower-middle faces
        {5, 10, 6, 0x28, { 0.35682f,  0.00000f,  0.93417f}},
        {3,  5, 12, 0x29, {-0.57735f, -0.57735f,  0.57735f}},
        {7,  3, 11, 0x2A, {-0.57735f, -0.57735f, -0.57735f}},
        {9,  7,  8, 0x2B, { 0.35682f,  0.00000f, -0.93417f}},
        {10, 9,  2, 0x2C, { 0.93417f,  0.35682f,  0.00000f}},
    };

    Scene scene;
    int vertexCount = sizeof(vertices) / sizeof(vertices[0]);
    int faceCount = sizeof(faces) / sizeof(faces[0]);
    scene.vertices = (Vec3*)vertices;
    scene.transformedVertices = (Vec3*)malloc(sizeof(Vec3) * vertexCount);
    scene.faces = (Face*)faces;
    scene.vertexCount = vertexCount;
    scene.faceCount = faceCount;
    scene.rot.x = 0.02; // Set rotation speed for x-axis
    scene.rot.y = 0.02; // Set rotation speed for y-axis
    scene.rot.z = 0.02; // Set rotation speed for z-axis
    return scene;
}

#endif // ICOSHDRN_H