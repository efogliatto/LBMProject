#ifndef BASICSOLVERINFO_H
#define BASICSOLVERINFO_H

#include <timeInfo.h>
#include <latticeInfo.h>
#include <mpiInfo.h>


struct fieldsInfo {

    c_scalar** colMat;
    c_scalar** colMatA;
    c_scalar** colMatB;

    c_scalar** srcMat;
    c_scalar** srcMatA;
    c_scalar** srcMatB;
    
    c_scalar sigma;
    c_scalar D;
    c_scalar phi_A;
    c_scalar phi_B;
    c_scalar M_phi;
    c_scalar gx;
    c_scalar gy;
    c_scalar gz;
    c_scalar rho_A;
    c_scalar rho_B;
    c_scalar eta;
    c_scalar beta;
    c_scalar kappa;
    
};






struct solverInfo {

    struct timeInfo time;

    struct latticeInfo lattice;

    struct fieldsInfo fields;

    struct mpiInfo parallel;
};



#endif // BASICSOLVERINFO_H
