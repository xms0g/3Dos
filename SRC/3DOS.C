#include "vec.h"
#include "matx.h"
#include "math.h"
#include "vga.h"
#include "tringl.h"
#include "keybrd.h"
#include "cvec.h"
#include "rndr.h"
#include "cvec.h"
#include "cube.h"
#include "icoshdrn.h"
#include "tree.h"
#include "f22.h"

#define WIDTH 320
#define HEIGHT 200
#define HALF_WIDTH 160
#define HALF_HEIGHT 100
#define FOV_FACTOR 280

static Vec3 rot;
static Vec3 cameraPos;
static Vec3 lightDir;
static CVEC triangles;
static int isRunning;
static Scene scene;

static void processInput(void) {
    if (kbHit(ESC)) {
        isRunning = 0;
    } else if (kbHit(W)) {
        cameraPos.z -= 0.1; 
    } else if (kbHit(S)) {
        cameraPos.z += 0.1; 
    } else if (kbHit(A)) {
        cameraPos.x += 0.1; 
    } else if (kbHit(D)) {
        cameraPos.x -= 0.1;
    } else if (kbHit(U_ARROW)) {
        cameraPos.y += 0.1;
    } else if (kbHit(D_ARROW)) {
        cameraPos.y -= 0.1;
    } else if (kbHit(NUM_1)) {
        free(scene.transformedVertices);
        vecZero(&rot);
        scene = cube();
    } else if (kbHit(NUM_2)) {
        free(scene.transformedVertices);
        vecZero(&rot);
        scene = icosahedron();
    } else if (kbHit(NUM_3)) {
        free(scene.transformedVertices);
        vecZero(&rot);
        scene = tree();
    } else if (kbHit(NUM_4)) {
        free(scene.transformedVertices);
        vecZero(&rot);
        scene = f22();
    }
}

static void update() {
    int i, j;
    Vec3 cameraRay;
    Mat3 rotMat;
    Triangle projectedTriangle;
    
    // Rotate the scene
    vecAdd(&rot, &rot, &scene.rot);
    vecWrap(&rot, TWO_PI);
    mtxRot(&rotMat, &rot);

    for (i = 0; i < scene.vertexCount; ++i) {
        Vec3 transformedVertex;
        const Vec3 vertex = scene.vertices[i];

        // Rotate the vertex around the cube's center
        mtxMulVec3(&transformedVertex, &rotMat, &vertex);

        // Translate the vertex away from the camera
        transformedVertex.z = transformedVertex.z - cameraPos.z;

        // Save transformed vertex in the array of transformed vertices
        scene.transformedVertices[i] = transformedVertex;
    }

    for (i = 0; i < scene.faceCount; ++i) {
        Vec3 transformedNormal;
        double lightIntensity;
        const Face f = scene.faces[i];

        // Rotate the face normal
        mtxMulVec3(&transformedNormal, &rotMat, &f.normal);

        scene.faceVertices[0] = scene.transformedVertices[f.a];
        scene.faceVertices[1] = scene.transformedVertices[f.b];
        scene.faceVertices[2] = scene.transformedVertices[f.c];

        vecSub(&cameraRay, &cameraPos, &scene.faceVertices[0]);

        // Backface Culling
        if (vecDot(&transformedNormal, &cameraRay) < 0) 
            continue;

        for (j = 0; j < 3; ++j) {
            Vec2 pv;
            Vec3 cameraView;
            const Vec3 fv = scene.faceVertices[j];
            
            // Convert points to camera's local coordinate system
            vecSub(&cameraView, &fv, &cameraPos);
            
            // Project the points onto the screen
            vecProject(&pv, &cameraView, FOV_FACTOR);
            pv.x += HALF_WIDTH;
            pv.y += HALF_HEIGHT;
            
            projectedTriangle.points[j] = pv;
        }

        lightIntensity = vecDot(&transformedNormal, &lightDir);
        projectedTriangle.lightIntensity = clamp(lightIntensity, 0.0, 1.0);
        projectedTriangle.color = f.color;
        
		cvPushback(&triangles, &projectedTriangle);
    }    
}

static void render(void) {
    int i;

    vgaClearOffscreen(0x03);

    for (i = 0; i < triangles.count; ++i) {
        const Triangle* tri = (Triangle*)cvAt(&triangles, i);

        // Draw filled triangle
        rndDrawFilledTri(
            tri->points[0].x, tri->points[0].y, // vertex A
            tri->points[1].x, tri->points[1].y, // vertex B
            tri->points[2].x, tri->points[2].y, // vertex C
            tri->color,
            tri->lightIntensity
        );  
    }

   	cvClear(&triangles);

    vgaUpdateVram();
}

void main(void) {
    cameraPos.x = 0.0;
    cameraPos.y = 0.0;
	cameraPos.z = 5.0;

    lightDir.x = 0.0;
    lightDir.y = 0.0;
    lightDir.z = 1.0;
    
    rot.x = 0.0;
    rot.y = 0.0;
    rot.z = 0.0;

    isRunning = 1;

    vgaInit();
    kbInit();

	cvInit(&triangles, 10, sizeof(Triangle));
    initSinCosLUT();

    scene = cube(); // Start with the cube scene
	while (isRunning) {
        processInput();
        update();
        render();
    }

	cvFree(&triangles);
    free(scene.transformedVertices);

    vgaExit();
    kbExit();
}
