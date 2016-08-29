#include <cahnHilliardCollision.h>
#include <cahnHilliardEquilibrium.h>
#include <stdlib.h>
#include <stdio.h>

void cahnHilliardCollision(struct twoPhasesFields* fields, struct solverInfo* info) {


    // Create equilibrium distribution vector
    double* eq = (double*)malloc( info->lattice.Q * sizeof(double) );
    double* st = (double*)malloc( info->lattice.Q * sizeof(double) );

    // Source term
    double* R = (double*)malloc( info->lattice.Q * sizeof(double) );

    // Move over local points
    unsigned int id, k;
    

    for( id = 0 ; id < info->lattice.nlocal ; id++ ) {
	
    	// Compute equilibrium value
    	cahnHilliardEquilibrium(fields, info, eq, id);

    	// Compute source term
    	cahnHilliardSource(fields, info, R, id);
	
    	// Assign auxiliary value
    	for( k = 0 ; k < info->lattice.Q ; k++ ) {

    	    eq[k] = eq[k] - fields->h[id][k];

    	}

    	// Extra multiplication
    	matVecMult(info->fields.colMat, eq, st, info->lattice.Q);

    	// Assign to node
    	for( k = 0 ; k < info->lattice.Q ; k++ ) {

    	    fields->h[id][k] += st[k] + R[k];

    	}

    }



    free(st);
    free(R);
    free(eq);
    
    // Sync fields
    syncPdfField( info, fields->h, info->lattice.Q );
    
    
}
