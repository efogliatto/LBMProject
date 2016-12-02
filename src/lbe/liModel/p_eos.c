#include <p_eos.h>
#include <stdio.h>
#include <math.h>

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

    
    // Peng - Robinson
    case 2:
	alpha = 0.170151343 * info->fields._a / (info->fields._b * info->fields._R); 
	beta = pow(  (1 + (0.37464+1.5422*info->fields._omega-0.26992*info->fields._omega*info->fields._omega)*(1-sqrt(T/alpha)))  , 2);
	p = rho * info->fields._R * T / ( 1 - info->fields._b * rho)    -   info->fields._a * beta * rho * rho / (1 + 2 * info->fields._b * rho - info->fields._b * rho * info->fields._b * rho);
	break;


	
    }    
    
    return p;
    
}
