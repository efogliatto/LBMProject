#ifndef LBEFIELD_H
#define LBEFIELD_H

#include <stdio.h>

struct lbeField {

    
    // Distribution functions
    double** value;

    // Swap value
    double** swap;
    
    // Field name
    char* name;
    
    // Collision model id
    // 0: Li MRT 
    // 1: Li SRT
    // 2: Li SRT for temperature
    unsigned int colId;
    
    // Single relaxation time
    double tau;

    // Multiple relaxation times
    double* Lambda;



    // Pointers to relaxation times. Allocation depends on colId
    // Relaxation times depend linearly on other parameters, e.g. density, temperature
    // e.g.    tau = tau_A + tau_B * p
    
    // Single relaxation times
    double tau_A;
    double tau_B;


    // Multiple relaxation times. Inverse values for linear interpolation
    double* inv_Lambda_A;
    double* inv_Lambda_B;


    double sigma;
    
};

#endif // LBEFIELD_H
