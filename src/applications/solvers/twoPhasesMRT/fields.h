#ifndef FIELDS_H
#define FIELDS_H

struct twoPhaseFields {

    double* phi;

    double* muPhi;

    double* rho;

    double* p;

    double** U;

    double** h;

    double** g;
    
};

#endif // FIELDS_H
