#include <stdio.h>
#include <stdlib.h>
#include "data.h"

void CHequilibrium(double* eq, const double* muPhi, const double* phi, const double** U, const struct lattice lat, const struct fields fld, const int id) {

    int vel[9][3];

    // Model velocity
    vel[0][0] = 0;
    vel[0][1] = 0;
    vel[0][0] = 0;
    
    vel[1][0] = -1;
    vel[1][1] = 0;
    vel[1][0] = 0;

    vel[2][0] = 0;
    vel[2][1] = -1;
    vel[2][0] = 0;

    vel[3][0] = 1;
    vel[3][1] = 0;
    vel[3][0] = 0;

    vel[4][0] = 0;
    vel[4][1] = 1;
    vel[4][0] = 0;

    vel[5][0] = -1;
    vel[5][1] = -1;
    vel[5][0] = 0;

    vel[6][0] = 1;
    vel[6][1] = -1;
    vel[6][0] = 0;

    vel[7][0] = 1;
    vel[7][1] = 1;
    vel[7][0] = 0;

    vel[8][0] = -1;
    vel[8][1] = 1;
    vel[8][0] = 0;
    



    double omega[9];

    omega[0] = 4.0 / 9.0;
    omega[1] = 1.0 / 9.0;
    omega[2] = 1.0 / 9.0;
    omega[3] = 1.0 / 9.0;
    omega[4] = 1.0 / 9.0;
    omega[5] = 1.0 / 36.0;
    omega[6] = 1.0 / 36.0;
    omega[7] = 1.0 / 36.0;
    omega[8] = 1.0 / 36.0;
    omega[9] = 1.0 / 36.0;
    

    
    unsigned int k;
    
    eq[0] = phi[id] + (omega[0] -1) * fld.eta * muPhi[id];

    for( k = 1 ; k < lat.Q ; k++ ) {
	const double dot = (vel[k][0] * U[k][0]) + (vel[k][1] * U[k][1]) + (vel[k][2] * U[k][2]);
    	eq[k] = omega[k] * fld.eta * muPhi[id]   +   lat.c * dot * omega[k] * phi[id] / lat.cs2;
    }
    
}
