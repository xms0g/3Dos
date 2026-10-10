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
        {1, 5, 6, 0x06, {0,0,-1}},
        {1, 6, 2, 0x06, {0,0,-1}},

        // Trunk: right
        {2, 6, 7, 0x06, {1,0,0}},
        {2, 7, 3, 0x06, {1,0,0}},

        // Trunk: back
        {3, 7, 8, 0x06, {0,0,1}},
        {3, 8, 4, 0x06, {0,0,1}},

        // Trunk: left
        {4, 8, 5, 0x06, {-1,0,0}},
        {4, 5, 1, 0x06, {-1,0,0}},

        // Layer 1 — darkest green
        {9, 13, 10,  0x02, { 0, 0,-1}},
        {10, 13, 11, 0x02, { 1, 0, 0}},
        {11, 13, 12, 0x0A, { 0, 0, 1}},
        {12, 13, 9,  0x02, {-1, 0, 0}},

        // Layer 2
        {14, 18, 15, 0x02, { 0, 0,-1}},
        {15, 18, 16, 0x0A, { 1, 0, 0}},
        {16, 18, 17, 0x0A, { 0, 0, 1}},
        {17, 18, 14, 0x02, {-1, 0, 0}},

        // Layer 3
        {19, 23, 20, 0x0A, { 0, 0,-1}},
        {20, 23, 21, 0x02, { 1, 0, 0}},
        {21, 23, 22, 0x0A, { 0, 0, 1}},
        {22, 23, 19, 0x02, {-1, 0, 0}},

        // Layer 4 — bright green top
        {24, 28, 25, 0x0A, { 0, 0,-1}},
        {25, 28, 26, 0x0A, { 1, 0, 0}},
        {26, 28, 27, 0x0A, { 0, 0, 1}},
        {27, 28, 24, 0x0A, {-1, 0, 0}}
    };

    Scene scene;
    scene.vertices = (Vec3*)vertices;
    scene.transformedVertices = (Vec3*)malloc(sizeof(Vec3) * 28);
    scene.faces = (Face*)faces;
    scene.vertexCount = 28;
    scene.faceCount = sizeof(faces) / sizeof(faces[0]);
    scene.rot.x = 0.0; // Set rotation speed for x-axis
    scene.rot.y = 0.02; // Set rotation speed for y-axis
    scene.rot.z = 0.0; // Set rotation speed for z-axis
    return scene;
}

#endif