#include <p_eos.h>
#include <stdio.h>

double p_eos( struct liModelInfo* info, double rho, double T ) {

    double p = 0, alpha, beta;

    switch( info->fields._eosIdx ) {
    
    // Ideal Gas
    case 0:
	p = rho * info->fields._R * T;
	break;
    

    // Carnahan - Starling
    case 1:
	alpha = info->fields._b * rho / 4;
	beta  = 1 - alpha; 
	p = rho * info->fields._R * T * ( (1 + alpha + alpha*alpha - alpha*alpha*alpha) / ( beta*beta*beta )  ) - info->fields._a * rho * rho;
	break;

    }
    
    return p;
    
}
