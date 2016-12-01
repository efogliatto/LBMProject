#include <interactionForce.h>
#include <potential.h>
#include <stdlib.h>
#include <stdio.h>

void interactionForce( struct liModelInfo* info, double F[3], double* rho, int** nb, double* T, unsigned int id ) {

    unsigned int i,
	k,
	noneigh = 0;

    // Initialize force term
    for( i = 0 ; i < 3 ; i++) {

	F[i] = 0 ;

    }

    
    // Move over neighbours
    for( k = 0 ; k < info->lattice.Q ; k++ ) {

    	int neighId = nb[id][k];

	// Do not compute interaction force (fluid-fluid) over boundary nodes
    	if( neighId == -1 ) {
	    
    	    /* neighId = nb[ id ][ info->lattice.reverse[k] ]; */
	    noneigh++;
	    
    	}
	
    	// Do not use unexisting neighbour
    	if(  ( neighId != -1 )  &&  (noneigh == 0)  ) {

    	    double alpha = info->lattice.weights[k] * potential(info, rho[neighId], T[neighId]) * info->lattice.c;
	    
    	    for( i = 0 ; i < 3 ; i++ ) {

    		F[i] +=  alpha * info->lattice.vel[ info->lattice.reverse[k] ][i] ;

    	    }

    	}

    }




    if(noneigh == 0) {
	
	// Extra constant
	double beta = -info->fields._G * potential(info, rho[id], T[id]);
    
	for( i = 0 ; i < 3 ; i++) {
	
	    F[i] =  F[i] * beta;
	
	}

    }

    else {

	for( i = 0 ; i < 3 ; i++) {
	
	    F[i] =  0;
	
	}

    }

    
    
}
