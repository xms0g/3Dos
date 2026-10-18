#ifndef CVEC_H
#define CVEC_H

typedef struct {    
    int count;      
    int capacity;
    int item_size;   
    void* data;     
} cvec;   

int cv_init(cvec* cv, int capacity, int item_size);

int cv_pushback(cvec* cv, void* item);

void* cv_at(cvec* cv, int index);

void cv_clear(cvec* cv);

void cv_free(cvec* cv);

#endif