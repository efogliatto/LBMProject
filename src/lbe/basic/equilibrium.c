#include <equilibrium.h>
#include <lbgkEquilibrium.h>

void equilibrium( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int id ) {

    
    // Apply equilibrium model according to field.colId
    switch(field->colId) {

	
    // Li model. MRT version
    case 0:
	lbgkEquilibrium( &mesh->lattice, mfields->rho[id], mfields->U[id], field->value[id]);
	break;

	
    // Li model. SRT version
    case 1:
	lbgkEquilibrium( &mesh->lattice, mfields->rho[id], mfields->U[id], field->value[id]);
	break;
	

    // Li model. Temperature
    case 2: 
	lbgkEquilibrium( &mesh->lattice, mfields->rho[id], mfields->U[id], field->value[id]);	
	unsigned int k;
	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {
	    field->value[id][k] = field->value[id][k] * mfields->Cv * mfields->T[id]; 
	}
	break;


    // Test SRT model.
    case 4:
	lbgkEquilibrium( &mesh->lattice, mfields->rho[id], mfields->U[id], field->value[id]);
	break;	
	
    default:
	break;
	
    }
    
}
