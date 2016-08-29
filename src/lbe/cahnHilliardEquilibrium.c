#include <cahnHilliardEquilibrium.h>
#include <stdio.h>

void cahnHilliardEquilibrium(struct twoPhasesFields* fields, struct solverInfo* info, double* eq, unsigned int id) {

    eq[0] = fields->phi[id] + (info->lattice.omega[0] - 1) * info->fields.eta * fields->muPhi[id];

    unsigned int k;
    double dot;
    
    for( k = 1 ; k < info->lattice.Q ; k++) {

	// Dot product: ci * U
    	dot = info->lattice.vel[k][0] * fields->U[id][0]   +   info->lattice.vel[k][1] * fields->U[id][1]   +   info->lattice.vel[k][2] * fields->U[id][2];
	
	// Equilibrium
    	eq[k] = info->lattice.omega[k] * info->fields.eta * fields->muPhi[id]   +   info->lattice.c * dot * info->lattice.omega[k] * fields->phi[id] / info->lattice.cs2;

    }


}
