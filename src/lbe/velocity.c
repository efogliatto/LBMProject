#include <velocity.h>
#include <scalarFieldGradient.h>
#include <scalarFieldLaplacian.h>
#include <stdlib.h>

void velocity( struct twoPhasesFields* fields, struct solverInfo* info, c_scalar** fld ) {

    unsigned int id, k;

    // Move over points
    for( id = 0 ; id < info->lattice.nlocal ; id++ ) {

	// Surface tension force
	c_scalar* Fs = scalarFieldGradient( fields, info, fields->phi, id );
	for( k = 0 ; k < 3 ; k++) {
	    Fs[k] = Fs[k] * fields->muPhi[id];
	}
	

	// Body force
	c_scalar Fb[3];
	Fb[0] = info->fields.gx * fields->rho[id];
	Fb[1] = info->fields.gy * fields->rho[id];
	Fb[2] = info->fields.gz * fields->rho[id];


	// Pdf reduction
	c_scalar red[3];
	red[0] = 0;
	red[1] = 0;
	red[2] = 0;
    
	for( k = 1 ; k < info->lattice.Q ; k++ ) {
	    red[0] += fields->g[id][k] * info->lattice.vel[k][0] * info->lattice.c;
	    red[1] += fields->g[id][k] * info->lattice.vel[k][1] * info->lattice.c;
	    red[2] += fields->g[id][k] * info->lattice.vel[k][2] * info->lattice.c;
	}


	c_scalar lap = scalarFieldLaplacian( fields, info, fields->muPhi, id );

	for( k = 0 ; k < 3 ; k++ ) {
	
	    fld[id][k] = ( red[k]  +  (Fs[k] + Fb[k]) * 0.5 * info->time.tstep )    /    ( fields->rho[id]  -  0.5 * info->time.tstep * (info->fields.rho_A - info->fields.rho_B) * info->fields.M_phi * lap / (info->fields.phi_A - info->fields.phi_B) );

	}

	free(Fs);

	
    }
    
}
