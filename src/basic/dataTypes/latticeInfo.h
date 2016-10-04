#ifndef LATTICEINFO_H
#define LATTICEINFO_H

#include <scalars_C.h>

struct latticeInfo {

    c_scalar size;
    c_scalar cs2;
    c_scalar c;
    unsigned int nlocal;
    int d;
    int Q;
    int** vel;
    int* reverse;
    c_scalar* omega;
    int principal[3][2];

    // Directional derivatives
    char* dd;

    double* weights;
    
};

#endif // LATTICEINFO_H
