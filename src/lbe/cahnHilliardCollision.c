#include <cahnHilliardCollision.h>
#include <stdlib.h>

void cahnHilliardCollision(struct twoPhasesFields* fields, const struct solverInfo* info) {


    // Create equilibrium distribution vector
    double* eq;
    eq = (double*)malloc( info->lattice.Q * sizeof(double) );

    // Source term
    double* R;
    R = (double*)malloc( info->lattice.Q * sizeof(double) );

    // Move over local points
    unsigned int id, k;
    for( id = 0 ; id < info->lattice.nlocal ; id++ ) {

	// Compute equilibrium value
	cahnHilliardEquilibrium(fields, info, eq, id);

	// Compute source term
	cahnHilliardSource(fields, info, R, id);
	

	// Assign node value
	for( k = 0 ; k < info->lattice.Q ; k++ ) {

	    fields->h[id][k] = eq[k];

	}

    }
    
    
}
