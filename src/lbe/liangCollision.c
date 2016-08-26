#include <liangCollision.h>
#include <stdlib.h>
#include <stdio.h>
#include <liangEquilibrium.h>
#include <liangSource.h>

void liangCollision(struct twoPhasesFields* fields, const struct solverInfo* info) {


    // Create equilibrium distribution vector
    double* eq = (double*)malloc( info->lattice.Q * sizeof(double) );
    double* st = (double*)malloc( info->lattice.Q * sizeof(double) );

    // Source term
    double* R = (double*)malloc( info->lattice.Q * sizeof(double) );

    // Move over local points
    unsigned int id, k;
    

    for( id = 0 ; id < info->lattice.nlocal ; id++ ) {

	// Compute equilibrium value
	liangEquilibrium(fields, info, eq, id);

	// Compute source term
	liangSource(fields, info, R, id);
	
	
	// Assign auxiliary value
	for( k = 0 ; k < info->lattice.Q ; k++ ) {

	    eq[k] = eq[k] - fields->g[id][k];

	}
	
	if( fields->phi[id] < 0 ) {
	
	    // Extra multiplication
	    matVecMult(info->fields.colMatA, eq, st, info->lattice.Q);

	}

	else {

	    // Extra multiplication
	    matVecMult(info->fields.colMatB, eq, st, info->lattice.Q);
	    
	}

	
	// Assign to node
	for( k = 0 ; k < info->lattice.Q ; k++ ) {

	    fields->g[id][k] += st[k] + R[k];

	}
	

	

    }



    
    free(st);
    free(R);
    free(eq);
    
}
