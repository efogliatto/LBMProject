#ifndef TWOPHASESFIELDS_H
#define TWOPHASESFIELDS_H

#include <scalars_C.h>

struct twoPhasesFields {

    c_scalar* phi;

    c_scalar* phi_old;

    c_scalar* muPhi;

    c_scalar* rho;

    c_scalar* p;

    c_scalar** U;
    
    c_scalar** U_old;

    c_scalar** h;

    c_scalar** g;

    c_scalar** swp;

    int** nb;
    
};

#endif // TWOPHASESFIELDS_H
