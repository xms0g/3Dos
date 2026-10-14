#ifndef TREE_H
#define TREE_H

#include "scene.h"

Scene tree() {
    static const Vec3 vertices[28] = {
        // Trunk: 0-7
        {-0.18f, 0.00f, -0.18f}, //  0
        { 0.18f, 0.00f, -0.18f}, //  1
        { 0.18f, 0.00f,  0.18f}, //  2
        {-0.18f, 0.00f,  0.18f}, //  3
        {-0.18f, 0.85f, -0.18f}, //  4
        { 0.18f, 0.85f, -0.18f}, //  5
        { 0.18f, 0.85f,  0.18f}, //  6
        {-0.18f, 0.85f,  0.18f}, //  7

        // Layer 1: wide bottom foliage
        {-0.85f, 0.65f, -0.85f}, //  8
        { 0.85f, 0.65f, -0.85f}, //  9
        { 0.85f, 0.65f,  0.85f}, // 10
        {-0.85f, 0.65f,  0.85f}, // 11
        { 0.00f, 1.75f,  0.00f}, // 12

        // Layer 2
        {-0.65f, 1.10f, -0.65f}, // 13
        { 0.65f, 1.10f, -0.65f}, // 14
        { 0.65f, 1.10f,  0.65f}, // 15
        {-0.65f, 1.10f,  0.65f}, // 16
        { 0.00f, 2.15f,  0.00f}, // 17

        // Layer 3
        {-0.45f, 1.55f, -0.45f}, // 18
        { 0.45f, 1.55f, -0.45f}, // 19
        { 0.45f, 1.55f,  0.45f}, // 20
        {-0.45f, 1.55f,  0.45f}, // 21
        { 0.00f, 2.55f,  0.00f}, // 22

        // Layer 4: small top
        {-0.28f, 1.95f, -0.28f}, // 23
        { 0.28f, 1.95f, -0.28f}, // 24
        { 0.28f, 1.95f,  0.28f}, // 25
        {-0.28f, 1.95f,  0.28f}, // 26
        { 0.00f, 2.95f,  0.00f}  // 27
    };


    static const Face faces[] = {
        // Trunk: front
        {0, 4, 5, 0x06, {0, 0, -1}},
        {0, 5, 1, 0x06, {0, 0, -1}},

        // Trunk: right
        {1, 5, 6, 0x06, {1, 0, 0}},
        {1, 6, 2, 0x06, {1, 0, 0}},

        // Trunk: back
        {2, 6, 7, 0x06, {0, 0, 1}},
        {2, 7, 3, 0x06, {0, 0, 1}},

        // Trunk: left
        {3, 7, 4, 0x06, {-1, 0, 0}},
        {3, 4, 0, 0x06, {-1, 0, 0}},

        // Layer 1 — darkest green
        {8, 12, 9,  0x02, {0, 0, -1}},
        {9, 12, 10, 0x02, {1, 0, 0}},
        {10, 12, 11, 0x02, {0, 0, 1}},
        {11, 12, 8,  0x02, {-1, 0, 0}},

        // Layer 2
        {13, 17, 14, 0x02, {0, 0, -1}},
        {14, 17, 15, 0x0A, {1, 0, 0}},
        {15, 17, 16, 0x0A, {0, 0, 1}},
        {16, 17, 13, 0x02, {-1, 0, 0}},

        // Layer 3
        {18, 22, 19, 0x0A, {0, 0, -1}},
        {19, 22, 20, 0x02, {1, 0, 0}},
        {20, 22, 21, 0x0A, {0, 0, 1}},
        {21, 22, 18, 0x02, {-1, 0, 0}},

        // Layer 4 — bright green top
        {23, 27, 24, 0x0A, {0, 0, -1}},
        {24, 27, 25, 0x0A, {1, 0, 0}},
        {25, 27, 26, 0x0A, {0, 0, 1}},
        {26, 27, 23, 0x0A, {-1, 0, 0}}
    };

    Scene scene;
    int vertexCount = sizeof(vertices) / sizeof(vertices[0]);
    int faceCount = sizeof(faces) / sizeof(faces[0]);
    scene.vertices = (Vec3*)vertices;
    scene.transformedVertices = (Vec3*)malloc(sizeof(Vec3) * vertexCount);
    scene.faces = (Face*)faces;
    scene.vertexCount = vertexCount;
    scene.faceCount = faceCount;
    scene.rot.x = 0.0; // Set rotation speed for x-axis
    scene.rot.y = 0.03; // Set rotation speed for y-axis
    scene.rot.z = 0.0; // Set rotation speed for z-axis
    return scene;
}

#endif