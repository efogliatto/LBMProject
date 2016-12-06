#include <macroVelocity.h>
#include <pseudoPotVelocity.h>
#include <stdlib.h>

void macroVelocity( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {

    
    // Apply collision model
    switch(field->colId) {

    // Li MRT Model
    case 0:
	pseudoPotVelocity( mesh, mfields, field );
	break;


    // Li SRT Model
    case 1:
	pseudoPotVelocity( mesh, mfields, field );
	break;
	
	
    default:
	printf("\n\n[ERROR]  Unable to compute macroscopic velocity with field %s \n\n", field->name);
	exit(1);
	break;	
	
    }

    
}
