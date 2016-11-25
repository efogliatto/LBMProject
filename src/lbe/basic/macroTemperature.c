#include <macroTemperature.h>
#include <pseudoPotTemperature.h>
#include <stdlib.h>

void macroTemperature( struct liModelInfo* info, struct macroFields* mfields, struct lbeField* field ) {

    
    // Apply collision model
    switch(field->colId) {

    // Li SRT Model
    case 2:
	pseudoPotTemperature( info, mfields, field->value );
	break;
	
    default:
	if(info->parallel.pid==0){ printf("\n\n[ERROR]  Unable to compute macroscopic temperature with field %s \n\n", field->name); }
	exit(1);
	break;	
	
    }

    
}
