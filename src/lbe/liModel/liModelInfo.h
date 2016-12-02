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
    c_scalar _omega;

    // Forcing scheme coefficients
    c_scalar sigma;
    c_scalar tau_e;
    c_scalar tau_c;


    // Temperature relaxation parameters
    double tau_T;

    // Constant specific heat
    c_scalar _Cv;;

    // EOS index
    // 0 : ideal gas
    // 1 : Carnahan-Starling
    unsigned int _eosIdx;


    // Gravity vector
    c_scalar _g[3];

    // Reference density
    c_scalar rho_0;
    
    
};





struct liModelInfo {

    struct timeInfo time;

    struct latticeInfo lattice;

    struct li_fieldsInfo fields;

    struct mpiInfo parallel;
};



#endif // BASICSOLVERINFO_H
