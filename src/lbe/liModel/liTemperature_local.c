#include <liTemperature_local.h>
#include <stdio.h>

void liTemperature_local( struct liModelInfo* info, struct macroFields* mfields, double** g, unsigned int id ) {

    unsigned int k;

    
    // Initialize Temperature
    double acum = 0;


    // Move over model velocities
    for(k = 0 ; k < info->lattice.Q ; k++) {

	acum += g[id][k];
		    
    }


    // Compute T
    mfields->T[id] = acum / (mfields->rho[id] * info->fields._Cv);
   

}
