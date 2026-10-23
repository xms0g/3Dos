#include "vec3.h"
#include "matx.h"
#include "math.h"
#include "vga.h"
#include "tringl.h"
#include "keybrd.h"
#include "cvec.h"
#include "rndr.h"
#include "qsort.h"
#include "cube.h"
#include "icoshdrn.h"
#include "tree.h"
#include "f22.h"

#define WIDTH 320
#define HEIGHT 200
#define HALF_WIDTH 160
#define HALF_HEIGHT 100
#define FOV_FACTOR 280

typedef struct {
    vec3 position;
    vec3 origin;
} camera;

typedef struct {
    vec3 direction;
} light;

static vec3 rot;
static camera cam;
static light l;
static cvec triangles;
static int is_running;
static mesh m;

static void process_input(void) {
    if (_kb_hit(ESC)) {
        is_running = 0;
    } else if (_kb_hit(W)) {
        cam.position.z -= 0.1; 
    } else if (_kb_hit(S)) {
        cam.position.z += 0.1; 
    } else if (_kb_hit(A)) {
        cam.position.x += 0.1; 
    } else if (_kb_hit(D)) {
        cam.position.x -= 0.1;
    } else if (_kb_hit(U_ARROW)) {
        cam.position.y += 0.1;
    } else if (_kb_hit(D_ARROW)) {
        cam.position.y -= 0.1;
    } else if (_kb_hit(NUM_1)) {
        free(m.transformed_vertices);
        vec3_zero(&rot);
        m = cube();
    } else if (_kb_hit(NUM_2)) {
        free(m.transformed_vertices);
        vec3_zero(&rot);
        m = icosahedron();
    } else if (_kb_hit(NUM_3)) {
        free(m.transformed_vertices);
        vec3_zero(&rot);
        m = tree();
    } else if (_kb_hit(NUM_4)) {
        free(m.transformed_vertices);
        vec3_zero(&rot);
        m = f22();
    }
}

static void update() {
    int i, j;
    vec3 camera_ray;
    mat3 rot_mat;
    triangle projected_triangle;
    vec3 face_vertices[3];

    cv_clear(&triangles);
    
    // Rotate the scene
    vec3_add(&rot, &rot, &m.rotation);
    vec3_wrap(&rot, TWO_PI);
    mtx_rot(&rot_mat, &rot);

    for (i = 0; i < m.vertex_count; ++i) {
        vec3 transformed_vertex;
        const vec3 vertex = m.vertices[i];

        // Rotate the vertex
        mtx_mul_vec3(&transformed_vertex, &rot_mat, &vertex);

        // Translate the vertex away from the camera
        vec3_sub(&transformed_vertex, &transformed_vertex, &cam.position);
        
        // Save transformed vertex in the array of transformed vertices
        m.transformed_vertices[i] = transformed_vertex;
    }

    for (i = 0; i < m.face_count; ++i) {
        vec3 transformed_normal;
        double light_intensity;
        double avg_depth;
        const face f = m.faces[i];

        // Rotate the face normal
        mtx_mul_vec3(&transformed_normal, &rot_mat, &f.normal);

        face_vertices[0] = m.transformed_vertices[f.a];
        face_vertices[1] = m.transformed_vertices[f.b];
        face_vertices[2] = m.transformed_vertices[f.c];

        vec3_sub(&camera_ray, &cam.origin, &face_vertices[0]);

        // Backface Culling
        if (vec3_dot(&transformed_normal, &camera_ray) < 0) 
            continue;

        for (j = 0; j < 3; ++j) {
            vec2 pv;
            const vec3 fv = face_vertices[j];
            
            // Project the points onto the screen
            vec3_project(&pv, &fv, FOV_FACTOR);
            
            pv.x += HALF_WIDTH;
            pv.y += HALF_HEIGHT;
            
            projected_triangle.points[j] = pv;
        }

        avg_depth = (face_vertices[0].z + face_vertices[1].z + face_vertices[2].z) / 3.0;
        projected_triangle.avg_depth = avg_depth;
        
        light_intensity = vec3_dot(&transformed_normal, &l.direction);
        projected_triangle.light_intensity = clamp(abs(light_intensity), 0.0, 1.0);
        
        projected_triangle.color = f.color;
        
		cv_pushback(&triangles, &projected_triangle);
    }

    // Painter's algorithm.Sorting ascending order because camera looks along -Z
    quick_sort(&triangles, 0, triangles.count - 1); 
}

static void render(void) {
    int i;

    _vga_clr_offscreen(0x03);

    for (i = 0; i < triangles.count; ++i) {
        const triangle* tri = CV_AT(triangle, &triangles, i);

        // Draw filled triangle
        rnd_draw_filled_tri(
            tri->points[0].x, tri->points[0].y, // vertex A
            tri->points[1].x, tri->points[1].y, // vertex B
            tri->points[2].x, tri->points[2].y, // vertex C
            tri->color,
            tri->light_intensity
        );  
    }

    _vga_blit();
}

void main(void) {
    cam.position.x = 0.0;
    cam.position.y = 0.0;
	cam.position.z = 5.0;

    cam.origin.x = 0.0;
    cam.origin.y = 0.0;
	cam.origin.z = 0.0;

    l.direction.x = 0.0;
    l.direction.y = 0.0;
    l.direction.z = -1.0;
    
    rot.x = 0.0;
    rot.y = 0.0;
    rot.z = 0.0;

    is_running = 1;

    _vga_init();
    _kb_init();

	cv_init(&triangles, 10, sizeof(triangle));
    init_sincos_lut();

    m = cube(); // Start with the cube mesh
	while (is_running) {
        process_input();
        update();
        render();
    }

	cv_free(&triangles);
    free(m.transformed_vertices);

    _vga_exit();
    _kb_exit();
}
