#include <testSRTCollision.h>
#include <syncPdfField.h>
#include <testEquilibrium.h>
#include <stdlib.h>


void testSRTCollision( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {

    
    // Indices
    unsigned int id, k;
    
    // Partial distributions
    double* feq = (double*)malloc( mesh->lattice.Q * sizeof(double) );
 

    // Move over points
    for( id = 0 ; id < mesh->lattice.nlocal ; id++ ) {

	// Compute equilibrium
	testEquilibrium(&mesh->lattice, &mesh->EOS, mfields->rho[id], mfields->U[id], mfields->T[id], feq);

	
	// Collide field
	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

	    field->value[id][k] = field->value[id][k]   -   (1/field->tau) * ( field->value[id][k] - feq[k] );

	}

    }


    // Deallocate memory
    free(feq);


    // Synchronize field
    syncPdfField( &mesh->parallel, field->value, mesh->lattice.Q );


}
