#include <macroDensity.h>
#include <liDensity.h>
#include <stdlib.h>

void macroDensity( struct liModelInfo* info, struct macroFields* mfields, struct lbeField* field ) {

    // Apply collision model
    switch(field->colId) {

    // Li MRT Model
    case 0:
	liDensity( info, mfields->rho, field->value );
	break;


    // Li SRT Model
    case 1:
	liDensity( info, mfields->rho, field->value );
	break;
	
	
    default:
	printf("\n\n[ERROR]  Model not available \n\n");
	exit(1);
	break;	
	
    }

}
