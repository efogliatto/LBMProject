#include <pressureWithU.h>

void pressureWithU( struct twoPhasesFields* fields, const struct solverInfo* info, double* fld ) {

    unsigned int id, k;

    // Move over points
    for( id = 0 ; id < info->lattice.nlocal ; id++ ) {

	// Pdf reduction, excluding first element
	double red = 0;
	for( k = 1 ; k < info->lattice.Q ; k++ ) {

	    red += fields->g[id][k];

	}

	// Dot product: U * grad(rho)
	double* rhoGrad;
	rhoGrad = scalarFieldGradient( fields, info, fields->rho, id );
	double dot = fields->U[id][0] * rhoGrad[0]   +   fields->U[id][1] * rhoGrad[1]   +   fields->U[id][2] * rhoGrad[2];

	// Equilibrium source term
	double Umag  = fields->U[id][0] * fields->U[id][0]  +  fields->U[id][1] * fields->U[id][1]  +  fields->U[id][2] * fields->U[id][2];
	double UdotC = info->lattice.c * ( fields->U[id][0] * info->lattice.vel[0][0]   +   fields->U[id][1] * info->lattice.vel[0][1]   +   fields->U[id][2] * info->lattice.vel[0][2] );
	double s_eq  = info->lattice.omega[0]  *  (  UdotC / info->lattice.cs2   +   UdotC * UdotC * 0.5 / (info->lattice.cs2 * info->lattice.cs2)   -  Umag * 0.5 / info->lattice.cs2 );	
	
	// Pressure at node
	fld[id] = ( info->lattice.cs2 / (1 - info->lattice.omega[0]) )  *  ( red   +  dot  * 0.5 * info->time.tstep   +   fields->rho[id] * s_eq );
	

    }
    
}


/* // Pdf reduction (except first value) */
/* pdf val = (*this).value(); */
/* const double red = val.reduce() - val[0]; */
	
/* // Extra constants */
/* const double w0 = _field->_lbm->omega(0); */
	
/* return ( _field->_cs2 / (1 - w0) )  *  ( red   +   (  (*_U) * _rho.gradient() ) * 0.5 * _field->_time.timeStep()   +   (*_rho) * s_eq(0,U) ); */
