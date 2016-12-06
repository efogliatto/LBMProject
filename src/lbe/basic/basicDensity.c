#include <basicDensity.h>
#include <syncScalarField.h>

void basicDensity( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {

    unsigned int i, k;
    
    // Move over points
    for( i = 0 ; i < mesh->lattice.nlocal ; i++ ) {

	mfields->rho[i] = 0;
	
	// Move over velocities
	for(k = 0 ; k < mesh->lattice.Q ; k++) {

	    mfields->rho[i] += field->value[i][k];

	}

    }


    // Synchronize field
    syncScalarField( &mesh->parallel, mfields->rho );
	
}
