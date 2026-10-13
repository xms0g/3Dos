#include "cvec.h"
#include <stdlib.h>

int cvInit(CVEC* cv, int capacity, int itemSize) {
    if (cv == NULL || capacity <= 0 || itemSize <= 0) {
        return -1;
    }

    cv->count = 0;
    cv->capacity = capacity;
    cv->itemSize = itemSize;
    cv->data = (void*)malloc(capacity * cv->itemSize);
    
    if (cv->data == NULL) {
        return -1;
    }

    return 0;
}

int cvPushback(CVEC* cv, void* item) {
    char* dest;
    char* new;

    if (cv == NULL || item == NULL) {
        return -1;
    }

    if (cv->count == cv->capacity) {
        cv->capacity *= 2;
        new = (char*)realloc(cv->data, cv->capacity * cv->itemSize);
        
        if (new == NULL) {
            return -1;
        }
        
        cv->data = new;
    }

    dest = (char*)cv->data + (cv->count * cv->itemSize);
    memcpy(dest, item, cv->itemSize);
    cv->count++;

    return 0;
}

void* cvAt(CVEC* cv, int index) {
    if (cv == NULL || index < 0 || index >= cv->count) {
        return NULL;
    }

    return (char*)cv->data + (index * cv->itemSize);
}

void cvClear(CVEC* cv) {
    cv->count = 0;
}

void cvFree(CVEC* cv) {
    free(cv->data);
    cv->data = NULL;
    
    cv->count = 0;
    cv->capacity = 0;
    cv->itemSize = 0;
}
