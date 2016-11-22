#include <interactionForce.h>
#include <potential.h>
#include <stdlib.h>

void interactionForce( struct liModelInfo* info, double F[3], double* rho, int** nb, double T, unsigned int id ) {

    unsigned int i,k;

    // Initialize force term
    for( i = 0 ; i < 3 ; i++) { F[i] = 0 ;}

    
    // Move over neighbours
    for( k = 0 ; k < info->lattice.Q ; k++ ) {

	int neighId = nb[id][k];
	
	// Do not use unexisting neighbour
	if( neighId != -1 ) {

	    double alpha = info->lattice.weights[k] * potential(info, rho[neighId], T) * info->lattice.c;
	    
	    for( i = 0 ; i < 3 ; i++ ) {

		F[i] +=  alpha * info->lattice.vel[ info->lattice.reverse[k] ][i] ;

	    }

	}

    }


    // Extra constant

    double beta = -info->fields._G * potential(info, rho[id], T);
    
    for( i = 0 ; i < 3 ; i++) {
	
	F[i] =  F[i] * beta   +   rho[id] * info->fields._g[i]; 
	
    }    

    
    
}
