#include <liDensity_local.h>

void liDensity_local( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int id ) {

    unsigned int k;
    
    mfields->rho[id] = 0;
	
    // Move over velocities
    for(k = 0 ; k < mesh->lattice.Q ; k++) {

	mfields->rho[id] += field->value[id][k];

    }

}
