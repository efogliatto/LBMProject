#ifndef TWOPHASESFIELDS_H
#define TWOPHASESFIELDS_H

struct twoPhasesFields {

    double* phi;

    double* phi_old;

    double* muPhi;

    double* rho;

    double* p;

    double** U;
    
    double** U_old;

    double** h;

    double** g;
    
};

#endif // TWOPHASESFIELDS_H
