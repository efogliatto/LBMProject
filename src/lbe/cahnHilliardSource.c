#include <cahnHilliardSource.h>
#include <matVecMult.h>
#include <stdlib.h>
/* #include <stdio.h> */

void cahnHilliardSource(struct twoPhasesFields* fields, const struct solverInfo* info, double* sourceTerm, const unsigned int id) {

    
    // First source term
    double* st;
    st = (double*)malloc( info->lattice.Q * sizeof(double) );

    // Temporal derivative
    const double ddt_x = (fields->U[id][0] * fields->phi[id])  -  (fields->U_old[id][0] * fields->phi_old[id]) / info->time.tstep;
    const double ddt_y = (fields->U[id][1] * fields->phi[id])  -  (fields->U_old[id][1] * fields->phi_old[id]) / info->time.tstep;
    const double ddt_z = (fields->U[id][2] * fields->phi[id])  -  (fields->U_old[id][2] * fields->phi_old[id]) / info->time.tstep;

    // Compute source term
    unsigned int i,j,k;
    for( k = 0 ; k < info->lattice.Q ; k++ ) {

    	const double dot = info->lattice.vel[k][0] * ddt_x   +   info->lattice.vel[k][1] * ddt_y   +   info->lattice.vel[k][2] * ddt_z;
	
    	st[k] = info->time.tstep * info->lattice.omega[k] * info->lattice.c * dot / info->lattice.cs2;

    }

    
    printf("lalala\n");
    
    // Multiplication with source matrix


    /* for( i = 0 ; i < info->lattice.Q ; i++ ) { */
    /* 	for( k = 0 ; k < info->lattice.Q ; k++ ) { */
    /* 	    printf("lalala\n"); */
    /* 	} */
    /* }	 */
    
    /* matVecMult(info->fields.srcM, st, sourceTerm, info->lattice.Q); */

    
    // Memory deallocation
    free(st);
    
    
}
