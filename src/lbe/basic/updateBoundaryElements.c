#include <updateBoundaryElements.h>
#include <liDensity_local.h>
#include <liVelocity_local.h>
#include <liTemperature_local.h>
#include <stdlib.h>
#include <stdio.h>

void updateBoundaryElements( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {

    unsigned int bndId, i, id;


    // Move over boundaries
    for( bndId = 0 ; bndId < mesh->bdElements._nb ; bndId++ ) {
	
	// Move over boundary elements
	for( i = 0 ; i < mesh->bdElements._nbel[bndId] ; i++ ) {

	    // Boundary element id
	    id = mesh->bdElements._idx[bndId][i];
	    

	    switch(field->colId) {

	    case 0:
		liDensity_local( mesh, mfields, field, id );
		liVelocity_local( mesh, mfields, field, id );
		break;

	    case 1:
		liDensity_local( mesh, mfields, field, id );
		liVelocity_local( mesh, mfields, field, id );
		break;

	    case 2:
		liTemperature_local( mesh, mfields, field, id );
		break;

	    default:
		if(mesh->parallel.pid == 0) { printf("\n\n\n[ERROR]  Unable to update boundary elements for field %s\n\n\n",field->name); }
		exit(1);
		break;

	    }


	}

    }

}
