#include <liangEquilibrium.h>
#include <stdlib.h>
#include <stdio.h>

void liangEquilibrium(struct twoPhasesFields* fields, struct solverInfo* info, c_scalar* eq, unsigned int id) {

    // Source term
    c_scalar* st = (c_scalar*)malloc( info->lattice.Q * sizeof(c_scalar) );

    // Compute source term
    unsigned int j, k;
    for( k = 0 ; k < info->lattice.Q ; k++) {

	// Dot product
	c_scalar dot = 0;
	for( j = 0 ; j < 3 ; j++ ) {
	    dot += info->lattice.c * info->lattice.vel[k][j] * fields->U[id][j];
	}


	// Velocity magnitude
	c_scalar Umag = 0;
	for( j = 0 ; j < 3 ; j++ ) {
	    Umag += fields->U[id][j] * fields->U[id][j];
	}
	
	st[k] = info->lattice.omega[k]  *  (  dot / info->lattice.cs2   +   dot * dot * 0.5 / (info->lattice.cs2 * info->lattice.cs2)   -  Umag * 0.5 / info->lattice.cs2 );

	

    }




    // Equilibrium
    eq[0] = fields->p[id] * (info->lattice.omega[0] - 1) / info->lattice.cs2   +   fields->rho[id] * st[0];

    for( k = 1 ; k < info->lattice.Q ; k++) {

	eq[k] = fields->p[id] * info->lattice.omega[k] / info->lattice.cs2   +   fields->rho[id] * st[k];
	
    }

    
    // Memory deallocation
    free(st);

}
