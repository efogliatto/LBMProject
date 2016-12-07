#include <updateTau.h>

void updateTau( struct lbeField* field, double r, unsigned int Q ) {
    
    if ( field->kappa_A != field->kappa_B ) {

	double c1, c2;

	c2 = (  field->tau_B  -  field->tau_A )  /  (field->kappa_B  -  field->kappa_A);

	c1 = field->tau_A - c2 * field->kappa_A;

	field->tau = c1  + c2 * r;

    }


    else {
	
	field->tau = field->tau_A;
    }
    
}
