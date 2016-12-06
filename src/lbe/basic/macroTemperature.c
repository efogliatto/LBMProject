#include <macroTemperature.h>
#include <pseudoPotTemperature.h>
#include <stdlib.h>

void macroTemperature( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {

    
    // Apply collision model
    switch(field->colId) {

    // Li SRT Model
    case 2:
	pseudoPotTemperature( mesh, mfields, field );
	break;
	
    default:
	if(mesh->parallel.pid==0){ printf("\n\n[ERROR]  Unable to compute macroscopic temperature with field %s \n\n", field->name); }
	exit(1);
	break;	
	
    }

    
}
