#include <liDensity_local.h>

void liDensity_local( struct liModelInfo* info, double* rho, double** f, unsigned int id ) {

    unsigned int k;
    
    rho[id] = 0;
	
    // Move over velocities
    for(k = 0 ; k < info->lattice.Q ; k++) {

	rho[id] += f[id][k];

    }

}
