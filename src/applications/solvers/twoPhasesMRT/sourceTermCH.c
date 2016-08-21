#include <stdio.h>
#include "data.h"
#include <stdlib.h>

double* latticeWeights(const struct lattice lat);
int** latticeVel(const struct lattice lat);


double* sourceTermCH(const double** U, const double** Uold, const double* phi, const double* phiOld, const struct lattice lat, const struct fields fld, const double dt, const int id) {

    double* st;
    st = (double*)malloc( lat.Q * sizeof(double) );

    double* omega;
    omega = latticeWeights(lat);

    int** lvel;
    lvel = latticeVel(lat);    
    
    const double ddt_x = (U[id][0] * phi[id]   -   Uold[id][0] * phiOld[id]) / dt;
    const double ddt_y = (U[id][1] * phi[id]   -   Uold[id][1] * phiOld[id]) / dt;
    const double ddt_z = (U[id][2] * phi[id]   -   Uold[id][2] * phiOld[id]) / dt;    
    
    unsigned int k;
    for(k = 0 ; k < lat.Q ; k++) {

	const double dot = lvel[k][0] * ddt_x  +  lvel[k][1] * ddt_y  +  lvel[k][2] * ddt_z;
	
	st[k] = omega[k] * lat.c * dot * dt / lat.cs2;
	
    }


    /* double* st2; */
    /* st2 = (double*)malloc( lat.Q * sizeof(double) ); */
    
    return st;
    
}
