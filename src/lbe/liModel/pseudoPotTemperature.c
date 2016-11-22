#include <pseudoPotTemperature.h>
#include <syncScalarField.h>
#include <stdio.h>

void pseudoPotTemperature( struct liModelInfo* info, struct macroFields* mfields, double** g ) {

    unsigned int id, k;

    
    // Move over points
    for( id = 0 ; id < info->lattice.nlocal ; id++ ) {

    	// Initialize Temperature
	double acum = 0;


	// Move over model velocities
	for(k = 0 ; k < info->lattice.Q ; k++) {

	    acum += g[id][k];
		    
	}


	// Compute T
	mfields->T[id] = acum / (mfields->rho[id] * info->fields._Cv);

    }


    // Synchronize field
    syncScalarField( &info->parallel, mfields->T );
    
}
