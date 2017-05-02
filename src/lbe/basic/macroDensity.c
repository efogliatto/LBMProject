#include <basicDensity.h>
#include <liDensity.h>
#include <stdlib.h>

void macroDensity( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {

    // Apply collision model
    switch(field->colId) {

    // Li MRT Model
    case 0:
	basicDensity( mesh, mfields, field );
	break;


    // Li SRT Model
    case 1:
	basicDensity( mesh, mfields, field );
	break;

	
    // Test SRT Model
    case 4:
	basicDensity( mesh, mfields, field );
	break;	
	
	
    default:
	printf("\n\n[ERROR]  Model not available \n\n");
	exit(1);
	break;	
	
    }

}
