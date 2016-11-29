#include <totalForce.h>
#include <stdio.h>

void totalForce( struct liModelInfo* info, double F[3], double* rho, int** nb, double* T, unsigned int id ) {

    unsigned int i;

    // Intermolecular interaction force
    interactionForce( info, F, rho, nb, T, id );


    // Addition of boundary force
    
    for( i = 0 ; i < 3 ; i++) {
	
    	F[i] +=  (rho[id] - info->fields.rho_0) * info->fields._g[i];
	
    }
    
    
}
