#include "cv.h"
#include <stdlib.h>

void cvInit(CVEC* cv, int capacity, int itemSize) {
    cv->count = 0;
    cv->capacity = capacity;
    cv->itemSize = itemSize;
    cv->data = (void*)malloc(capacity * cv->itemSize);
}

void cvPushback(CVEC* cv, void* item) {
    char* dest;
    if (cv->count == cv->capacity) {
        cv->capacity *= 2;
        cv->data = (void*)realloc(cv->data, cv->capacity * cv->itemSize);
    }

    dest = (char*)cv->data + (cv->count * cv->itemSize);
    memcpy(dest, item, cv->itemSize);
    cv->count++;
}

void* cvAt(CVEC* cv, int index) {
    if (index < 0 || index >= cv->count) {
        return NULL;
    }

    return (char*)cv->data + (index * cv->itemSize);
}

void cvClear(CVEC* cv) {
    memset(cv->data, 0, cv->count * cv->itemSize);
    cv->count = 0;
}

void cvFree(CVEC* cv) {
    free(cv->data);
    cv->data = NULL;
}
