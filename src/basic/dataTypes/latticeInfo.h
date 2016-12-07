#ifndef LATTICEINFO_H
#define LATTICEINFO_H

#include <scalars_C.h>

// Basically, DdQq model info

struct latticeInfo {

    // Lattice size (dx)
    c_scalar size;

    // Sound speed
    c_scalar cs2;

    // Lattice velocity
    c_scalar c;

    // Nomber of local elements
    unsigned int nlocal;

    // Dimmension
    int d;

    // Number of discrete velocities
    int Q;

    // DdQq model velocities
    int** vel;

    // DdQq model reverse indices
    int* reverse;
    
    // DdQq model weights
    c_scalar* omega;

    // Main lattice directions (not used)
    int principal[3][2];

    // Directional derivatives
    char* dd;

    // Interaction force weights
    double* weights;


    // MRT matrices
    double** M;
    double** invM;
    
};

#endif // LATTICEINFO_H
