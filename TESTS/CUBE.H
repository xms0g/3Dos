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
        {1, 2, 3, 0x50, {0, 0, -1}},
        {1, 3, 4, 0x51, {0, 0, -1}},
        // right
        {4, 3, 5, 0x40, {1, 0, 0}},
        {4, 5, 6, 0x41, {1, 0, 0}},
        // back
        {6, 5, 7, 0x22, {0, 0, 1}},
        {6, 7, 8, 0x23, {0, 0, 1}},
        // left
        {8, 7, 2, 0x2A, {-1, 0, 0}},
        {8, 2, 1, 0x2B, {-1, 0, 0}},
        // top
        {2, 7, 5, 0x28, {0, 1, 0}},
        {2, 5, 3, 0x29, {0, 1, 0}},
        // bottom
        {6, 8, 1, 0x36, {0, -1, 0}},
        {6, 1, 4, 0x37, {0, -1, 0}},
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

#endif