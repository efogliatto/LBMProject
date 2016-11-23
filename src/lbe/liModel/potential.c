#include <potential.h>
#include <p_eos.h>
#include <math.h>
#include <stdio.h>

double potential( struct liModelInfo* info, double rho, double T ) {
    
    return sqrt(
    	2 * ( p_eos(info,rho,T) - rho * info->lattice.cs2 ) / (info->lattice.c * info->lattice.c * info->fields._G)
    	);
    
}
