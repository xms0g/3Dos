#include "tringl.h"
#include <stdlib.h>

void taInit(TriArray* ta, int size) {
    ta->count = 0;
    ta->capacity = size;
    ta->data = (Triangle*)malloc(size * sizeof(Triangle));
}

void taPushback(TriArray* ta, Triangle* tri) {
    if (ta->count == ta->capacity) {
        ta->capacity *= 2;
        ta->data = (Triangle*)realloc(ta->data, ta->capacity * sizeof(Triangle));
    }

    ta->data[ta->count++] = *tri;
}

void taRemove(TriArray* ta, int index) {
    int i;

    if (index < 0 || index >= ta->count) {
        return;
    }
    
    for (i = index; i < ta->count - 1; i++) {
        ta->data[i] = ta->data[i + 1];
    }
    
    ta->count--;
}

Triangle* taAt(TriArray* ta, int index) {
    if (index < 0 || index >= ta->count) {
        return NULL;
    }

    return &ta->data[index];
}

void taClear(TriArray* ta) {
    memset(ta->data, 0, ta->count * sizeof(Triangle));
    ta->count = 0;
}

void taFree(TriArray* ta) {
    free(ta->data);
    ta->data = NULL;
}
