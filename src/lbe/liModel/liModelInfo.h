#ifndef BASICSOLVERINFO_H
#define BASICSOLVERINFO_H

#include <timeInfo.h>
#include <latticeInfo.h>
#include <mpiInfo.h>

#define MPI_BUFF_SIZE 100



struct li_fieldsInfo {

    // Model matrix (inverse)
    c_scalar** invM;

    // Collision matrix (\bar{\Lambda})
    c_scalar** Lambda;

    // Carnahan - Starling coefficients
    c_scalar _a;
    c_scalar _b;
    c_scalar _R;
    c_scalar _T;
    c_scalar _G;
    
    
};





struct liModelInfo {

    struct timeInfo time;

    struct latticeInfo lattice;

    struct li_fieldsInfo fields;

    struct mpiInfo parallel;
};



#endif // BASICSOLVERINFO_H
