#ifndef LBEFIELD_H
#define LBEFIELD_H

#include <stdio.h>

struct lbeField {

    
    // Distribution functions
    double** value;
    
    // Field name
    char* name;
    
    // Collision model id
    // 0: Modelo de Li MRT
    // 1: Modelo de Li SRT
    // 2: Modelo de Li SRT para temperatura. Con termino correctivo para colision
    unsigned int colId;
    
    // Single relaxation time
    double tau;

    // Multiple relaxation times
    double* Lambda;

    
};

#endif // LBEFIELD_H
