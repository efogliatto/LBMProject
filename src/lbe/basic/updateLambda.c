#include <updateLambda.h>

void updateLambda( struct lbeField* field, double r, unsigned int Q ) {

    unsigned int k;
    
    if ( field->kappa_A != field->kappa_B ) {

	double c1, c2;

	for( k = 0 ; k < Q ; k++ ) {

	    c2 = (  1/field->Lambda_B[k]  -  1/field->Lambda_A[k] )  /  (field->kappa_B  -  field->kappa_A);

	    c1 = 1/field->Lambda_A[k] - c2 * field->kappa_A;

	    field->Lambda[k] = 1/(c1  + c2 * r);

	}

    }


    else {

	for( k = 0 ; k < Q ; k++ ) {
	
	    field->Lambda[k] = field->Lambda_A[k];

	}
	
    }
    
}
