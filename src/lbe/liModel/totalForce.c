#include <totalForce.h>
#include <stdio.h>

void totalForce( struct latticeMesh* mesh, double F[3], double* rho, double* T, unsigned int id ) {

    unsigned int i;

    // Intermolecular interaction force
    interactionForce( mesh, F, rho, T, id );


    // Addition of boundary force
    
    for( i = 0 ; i < 3 ; i++) {
	
    	F[i] +=  (rho[id] - mesh->EOS.rho_0) * mesh->EOS._g[i];
	
    }
    
    
}
