#ifndef CUBE_H
#define CUBE_H

#include "scene.h"

Scene cube() {
    static const Vec3 vertices[8] = {
        {-1, -1, -1},
        {-1,  1, -1},
        { 1,  1, -1},
        { 1, -1, -1},
        { 1,  1,  1},
        { 1, -1,  1},
        {-1,  1,  1},
        {-1, -1,  1},
    };

    static const Face faces[12] = {
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

    Scene scene;
    int vertexCount = sizeof(vertices) / sizeof(vertices[0]);
    int faceCount = sizeof(faces) / sizeof(faces[0]);
    scene.vertices = (Vec3*)vertices;
    scene.transformedVertices = (Vec3*)malloc(sizeof(Vec3) * vertexCount);
    scene.faces = (Face*)faces;
    scene.vertexCount = vertexCount;
    scene.faceCount = faceCount;
    scene.rot.x = 0.03; // Set rotation speed for x-axis
    scene.rot.y = 0.03; // Set rotation speed for y-axis
    scene.rot.z = 0.03; // Set rotation speed for z-axis
    return scene;
}

#endif