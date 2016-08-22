#include <stdio.h>
#include <stdlib.h>
#include "data.h"


/* double* sourceTermCH(double** U, */
/* 		     double** Uold, */
/* 		     double* phi, */
/* 		     double* phiOld, */
/* 		     const double* omega, */
/* 		     const int** lvel, */
/* 		     const struct lattice lat, */
/* 		     const struct fields fld, */
/* 		     const double dt, */
/* 		     const int id); */

/* double** collisionMatrix(const */
/* 			 struct lattice lat, */
/* 			 const struct fields fld); */

void CHequilibrium(double* eq,
		   const double* muPhi,
		   const double* phi,
		   const double** U,
		   const struct lattice lat,
		   const struct fields fld,
		   const int id);

/* int** latticeVel(const struct lattice lat); */

/* double* latticeWeights(const struct lattice lat); */




void collideCahnHilliard(double** U, double** Uold, double* phi, double* phiOld, double* muPhi, double** h, const struct lattice lat, const struct fields fld, const double dt) {

    /* // Collision Matrix */
    /* double** Delta; */
    /* Delta = collisionMatrix(lat,fld); */

    // Equilibrium dist function
    double* eq;
    eq = (double*)malloc( lat.Q * sizeof(double) );

    /* // Swap value */
    /* double* res; */
    /* res = (double*)malloc( lat.Q * sizeof(double) ); */

    /* // Lattice Velocites */
    /* int** lvel; */
    /* lvel = latticeVel(lat); */

    /* // Model weights */
    /* double* omega; */
    /* omega = latticeWeights(lat);     */

    // Move over points and collide
    unsigned int id;
    for( id = 0 ; id < lat.nlocal ; id++) {

    	/* // Source term */
    	/* double* R; */
    	/* R = sourceTermCH(U, Uold, phi, phiOld, omega, lvel, lat, fld, dt, id); */

    	// Compute equilibrium
    	CHequilibrium(eq, muPhi, phi, U, lat, fld, id);

    	/* // Auxiliar pdf */
    	/* unsigned int j,k; */
    	/* for(j = 0 ; j < lat.Q ; j++) { */
    	/*     res[j] = 0; */
    	/*     for(k = 0 ; k < lat.Q ; k++) { */
    	/* 	res[j] += Delta[j][k] * (eq[k] - h[id][k]); */
    	/*     } */
    	/* } */

    	/* // Assign value to node */
    	/* for(j = 0 ; j < lat.Q ; j++) { */
    	/*     h[id][j] = h[id][j] + res[j];// + R[j]; */
    	/* } */
	
    }





}
