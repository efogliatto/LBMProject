#ifndef BASICSOLVERINFO_H
#define BASICSOLVERINFO_H

struct timeInfo {

    double start;
    double end;
    double tstep;
    double writeInterval;
    double current;
    
};

struct latticeInfo {

    double size;
    double cs2;
    double c;
    double nlocal;
    int d;
    int Q;
    int** vel;
    double* omega;
    
};

struct fieldsInfo {

    double** colMat;
    double** colMatA;
    double** colMatB;

    double** srcMat;
    double** srcMatA;
    double** srcMatB;
    
    double sigma;
    double D;
    double phi_A;
    double phi_B;
    double M_phi;
    double gx;
    double gy;
    double gz;
    double rho_A;
    double rho_B;
    double eta;
    double beta;
    double kappa;
    
};


struct solverInfo {

    struct timeInfo time;

    struct latticeInfo lattice;

    struct fieldsInfo fields;    
};

#endif // BASICSOLVERINFO_H
