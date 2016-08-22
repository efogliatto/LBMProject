#include <liangCollision.h>
#include <stdlib.h>

void liangCollision(struct twoPhasesFields* fields, const struct solverInfo* info) {


    // Create equilibrium distribution vector
    double* eq = (double*)malloc( info->lattice.Q * sizeof(double) );
    double* st = (double*)malloc( info->lattice.Q * sizeof(double) );

    // Source term
    double* R = (double*)malloc( info->lattice.Q * sizeof(double) );

    // Move over local points
    unsigned int id, k;
    

    for( id = 0 ; id < info->lattice.nlocal ; id++ ) {

	/* // Compute equilibrium value */
	/* cahnHilliardEquilibrium(fields, info, eq, id); */

	/* // Compute source term */
	/* cahnHilliardSource(fields, info, R, id); */
	
	/* // Assign auxiliary value */
	/* for( k = 0 ; k < info->lattice.Q ; k++ ) { */

	/*     eq[k] = eq[k] - fields->h[id][k]; */

	/* } */

	/* // Extra multiplication */
	/* matVecMult(info->fields.colMat, eq, st, info->lattice.Q); */

	/* // Assign to node */
	/* for( k = 0 ; k < info->lattice.Q ; k++ ) { */

	/*     fields->h[id][k] += st[k] + R[k]; */

	/* } */

    }

    
    
}





/* // Collide g */
/* for(std::pair<LiangField::iterator, latticeScalarField::iterator> it(g.begin(), phi.begin()) ; it.first != g.end() ; ++it.first, ++it.second) { */

/*     if (   (phi_A * it.second->value()) >= 0  ) { */
	    
/* 	// Source term */
/* 	pdf R = resMatrixG_A * it.first.totalForce() * runTime.timeStep(); */

/* 	// Collide */
/* 	it.first->setNodeValue( */
/* 	    it.first->value()    +   DeltaG_A * ( it.first.equilibrium() - it.first->value() )    +    R */
/* 	    ); */

/*     } */

/*     else { */

/* 	// Source term */
/* 	pdf R = resMatrixG_B * it.first.totalForce() * runTime.timeStep(); */

/* 	// Collide */
/* 	it.first->setNodeValue( */
/* 	    it.first->value()    +   DeltaG_B * ( it.first.equilibrium() - it.first->value() )    +    R */
/* 	    ); */
		
/*     } */

/* } */
