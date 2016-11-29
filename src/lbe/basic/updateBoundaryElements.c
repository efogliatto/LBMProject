#include <updateBoundaryElements.h>
#include <liDensity_local.h>
#include <liVelocity_local.h>
#include <liTemperature_local.h>
#include <stdlib.h>
#include <stdio.h>

void updateBoundaryElements( struct bdInfo* bdElements, struct lbeField* field, struct liModelInfo* info, struct macroFields* mfields, int** nb ) {

    unsigned int bndId, i, id;


    // Move over boundaries
    for( bndId = 0 ; bndId < bdElements->_nb ; bndId++ ) {
	
	// Move over boundary elements
	for( i = 0 ; i < bdElements->_nbel[bndId] ; i++ ) {

	    // Boundary element id
	    id = bdElements->_idx[bndId][i];

	    switch(field->colId) {

	    case 0:
		liDensity_local( info, mfields->rho, field->value, id );
		liVelocity_local( info, mfields->rho, mfields->U, field->value, nb, mfields->T, id );
		break;

	    case 1:
		liDensity_local( info, mfields->rho, field->value, id );
		liVelocity_local( info, mfields->rho, mfields->U, field->value, nb, mfields->T, id );
		break;

	    case 2:
		liTemperature_local( info, mfields, field->value, id );
		break;

	    default:
		if(info->parallel.pid == 0) { printf("\n\n\n[ERROR]  Unable to update boundary elements for field %s\n\n\n",field->name); }
		exit(1);
		break;

	    }


	}

    }

}
