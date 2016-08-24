#include <liangEquilibrium.h>

void liangEquilibrium(struct twoPhasesFields* fields, const struct solverInfo* info, double* eq, const unsigned int id) {

    // Source term. Use eq to save memory
    unsigned int k;
    for( k = 1 ; k < info->lattice.Q ; k++) {

	const double dot = info->lattice.c *  (info->lattice.vel[k][0] * fields->U[id][0]   +   info->lattice.vel[k][1] * fields->U[id][1]   +   info->lattice.vel[k][2] * fields->U[id][2] );

	const double Umag = fields->U[id][0] * fields->U[id][0]   +   fields->U[id][1] * fields->U[id][1]   +   fields->U[id][2] * fields->U[id][2] ;
	
	eq[k] = info->lattice.omega[k]  *  (  dot / info->lattice.cs2   +   dot * dot * 0.5 / (info->lattice.cs2 * info->lattice.cs2)   -  Umag * 0.5 / info->lattice.cs2 );

    }
    
    
    eq[0] = fields->p[id] * (info->lattice.omega[0] - 1) / info->lattice.cs2   +   fields->rho[id] * eq[0];


    for( k = 1 ; k < info->lattice.Q ; k++) {

	eq[k] = fields->p[id] * info->lattice.omega[0] / info->lattice.cs2   +   fields->rho[id] * eq[k];
	
    }

}


/* pdf s = s_eq(u->value()); */

/* // Equilibrium */
/* pdf eq; */
/* eq.resize( omega.size() ); */

/* eq[0] = (p->value() * (omega[0] - 1) / cs2)   +   rho->value() * s[0]; */

/* for(uint i = 1 ; i < omega.size() ; i++)  */
/*     eq[i] = ( p->value() * omega[i] / cs2 )   +   rho->value() * s[i]; */
