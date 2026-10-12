#ifndef CVEC_H
#define CVEC_H

typedef struct {    
    int count;      
    int capacity;
    int itemSize;   
    void* data;     
} CVEC;   

int cvInit(CVEC* cv, int capacity, int itemSize);

int cvPushback(CVEC* cv, void* item);

void* cvAt(CVEC* cv, int index);

void cvClear(CVEC* cv);

void cvFree(CVEC* cv);

#endif