#include <equilibrium.h>

void equilibrium( struct liModelInfo* info, struct macroFields* mfields, struct lbeField* field, unsigned int id ) {

    
    // Apply equilibrium model according to field.colId
    switch(field->colId) {

	
    // Li model. MRT version
    case 0:
	liEquilibrium(info, mfields->rho[id], mfields->U[id], field->value[id]);
	break;

	
    // Li model. SRT version
    case 1:
	liEquilibrium(info, mfields->rho[id], mfields->U[id], field->value[id]);
	break;
	

    // Li model. Temperature
    case 2: 
	liEquilibrium(info, mfields->rho[id], mfields->U[id], field->value[id]);
	unsigned int k;
	for( k = 0 ; k < info->lattice.Q ; k++ ) {
	    field->value[id][k] = field->value[id][k] * info->fields._Cv * mfields->T[id]; 
	}
	break;

	
    default:
	break;
	
    }
    
}
