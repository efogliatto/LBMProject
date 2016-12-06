#include <pseudoPotTemperature.h>
#include <syncScalarField.h>
#include <stdio.h>

void pseudoPotTemperature( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {

    unsigned int id, k;

    
    // Move over points
    for( id = 0 ; id < mesh->lattice.nlocal ; id++ ) {

    	// Initialize Temperature
	double acum = 0;


	// Move over model velocities
	for(k = 0 ; k < mesh->lattice.Q ; k++) {

	    acum += field->value[id][k];
		    
	}


	// Compute T
	mfields->T[id] = acum / (mfields->rho[id] * mfields->Cv);

    }


    // Synchronize field
    syncScalarField( &mesh->parallel, mfields->T );
    
}
