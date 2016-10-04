#include <liangCollision.h>
#include <stdlib.h>
#include <stdio.h>
#include <liangEquilibrium.h>
#include <liangSource.h>
#include <matVecMult.h>

void liangCollision(struct twoPhasesFields* fields, struct solverInfo* info) {


    // Create equilibrium distribution vector
    c_scalar* eq = (c_scalar*)malloc( info->lattice.Q * sizeof(c_scalar) );
    c_scalar* st = (c_scalar*)malloc( info->lattice.Q * sizeof(c_scalar) );

    // Source term
    c_scalar* R = (c_scalar*)malloc( info->lattice.Q * sizeof(c_scalar) );

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

    
    // Sync fields
    syncPdfField( &info->parallel, fields->g, info->lattice.Q );
    
}
