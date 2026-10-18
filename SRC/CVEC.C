#include "cvec.h"
#include <stdlib.h>

int cv_init(cvec* cv, int capacity, int item_size) {
    if (cv == NULL || capacity <= 0 || item_size <= 0) {
        return -1;
    }

    cv->count = 0;
    cv->capacity = capacity;
    cv->item_size = item_size;
    cv->data = (void*)malloc(capacity * cv->item_size);
    
    if (cv->data == NULL) {
        return -1;
    }

    return 0;
}

int cv_pushback(cvec* cv, void* item) {
    char* dest;
    char* new;

    if (cv == NULL || item == NULL) {
        return -1;
    }

    if (cv->count == cv->capacity) {
        cv->capacity *= 2;
        new = (char*)realloc(cv->data, cv->capacity * cv->item_size);
        
        if (new == NULL) {
            return -1;
        }
        
        cv->data = new;
    }

    dest = (char*)cv->data + (cv->count * cv->item_size);
    memcpy(dest, item, cv->item_size);
    cv->count++;

    return 0;
}

void* cv_at(cvec* cv, int index) {
    if (cv == NULL || index < 0 || index >= cv->count) {
        return NULL;
    }

    return (char*)cv->data + (index * cv->item_size);
}

void cv_clear(cvec* cv) {
    cv->count = 0;
}

void cv_free(cvec* cv) {
    free(cv->data);
    cv->data = NULL;
    
    cv->count = 0;
    cv->capacity = 0;
    cv->item_size = 0;
}
