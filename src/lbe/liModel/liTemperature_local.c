#include <liTemperature_local.h>
#include <stdio.h>

void liTemperature_local( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int id ) {

    unsigned int k;

    
    // Initialize Temperature
    double acum = 0;


    // Move over model velocities
    for(k = 0 ; k < mesh->lattice.Q ; k++) {

	acum += field->value[id][k];
		    
    }


    // Compute T
    mfields->T[id] = acum / (mfields->rho[id] * mfields->Cv);
   

}
