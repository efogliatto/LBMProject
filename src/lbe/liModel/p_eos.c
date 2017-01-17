#include <p_eos.h>
#include <stdio.h>
#include <math.h>

double p_eos( struct EOSInfo* info, double rho, double T ) {

    double p = 0, alpha, beta;

    switch( info->_eosIdx ) {
    
    // Ideal Gas
    case 0:
	p = rho * info->_R * T;
	break;
    

    // Carnahan - Starling
    case 1:
	alpha = info->_b * rho / 4;
	beta  = 1 - alpha; 
	p = rho * info->_R * T * ( (1 + alpha + alpha*alpha - alpha*alpha*alpha) / ( beta*beta*beta )  ) - info->_a * rho * rho;
	break;

    
    // Peng - Robinson
    case 2:	
	alpha = 0.170151343 * info->_a / (info->_b * info->_R); // Tc
	beta = (1 + (0.37464+1.5422*info->_omega-0.26992*info->_omega*info->_omega)*(1-sqrt(T/alpha))); // sqrt(phi)
	p = rho * info->_R * T / ( 1 - info->_b * rho)    -   info->_a * beta * beta * rho * rho / (1 + 2 * info->_b * rho - info->_b * rho * info->_b * rho);
	break;


    // van der Waals
    case 3:
	p = rho * info->_R * T / (info->_M - rho * info->_b)  -  info->_a * rho * rho / ( info->_M * info->_M );
	break;
	
	
    }    
    
    return p;
    
}
