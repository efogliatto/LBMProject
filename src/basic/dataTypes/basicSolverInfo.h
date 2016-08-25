#ifndef BASICSOLVERINFO_H
#define BASICSOLVERINFO_H

#include <time.h>
#include <sys/time.h>

struct timeInfo {

    // Simulation parameters

    // Start time
    double start;

    // End time
    double end;

    // Time step
    double tstep;

    // Write interval (write every writeInterval steps)
    unsigned int writeInterval;

    // Current time
    double current;

    // Start time (time measurement)
    time_t st;

    // Time step
    unsigned int stp;
    
};



struct latticeInfo {

    double size;
    double cs2;
    double c;
    unsigned int nlocal;
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
