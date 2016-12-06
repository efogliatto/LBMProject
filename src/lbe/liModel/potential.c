#include <potential.h>
#include <p_eos.h>
#include <math.h>
#include <stdio.h>

double potential( struct latticeMesh* mesh, double rho, double T ) {
    
    return sqrt(
    	2 * ( p_eos(&mesh->EOS,rho,T) - rho * mesh->lattice.cs2 ) / (mesh->lattice.c * mesh->lattice.c * mesh->EOS._G)
    	);
    
}
