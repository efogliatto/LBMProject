#include <stdio.h>
#include "data.h"

void collideCahnHilliard(double* phi,double* muPhi,double** U,double** h, const struct lattice lat) {

    /* // Source term */
    /* pdf R = resMatrix * it.source() * runTime.timeStep(); */

    /* // Collide */
    /* it->setNodeValue( */
    /* 	it->value()    +   Delta * ( it.equilibrium() - it->value() )    +    R */
    /* 	); */


    // Source term
    double** R;
    /* setSourceTerm(R,lat); */
    
}
