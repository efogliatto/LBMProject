#include <p_eos.h>

double p_eos( struct liModelInfo* info, double rho, double T ) {

    double p = 0;
    
    // Ideal Gas
    if( info->fields._eosIdx == 0 ) {
	p = rho * info->fields._R * T;
    }

    else {

	// Carnahan starling
	if ( info->fields._eosIdx == 1 ) {
    
	    double alpha = info->fields._b * rho / 4;
	    double beta  = 1 - alpha;

	    p = rho * info->fields._R * T * ( (1 + alpha + alpha*alpha - alpha*alpha*alpha) / ( beta*beta*beta )  ) - info->fields._a * rho * rho;

	}

    }

    return p;
    
}
