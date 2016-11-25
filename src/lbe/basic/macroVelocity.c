#include <macroVelocity.h>
#include <pseudoPotVelocity.h>
#include <stdlib.h>

void macroVelocity( struct liModelInfo* info, struct macroFields* mfields, struct lbeField* field, int** nb ) {

    
    // Apply collision model
    switch(field->colId) {

    // Li MRT Model
    case 0:
	pseudoPotVelocity( info, mfields->rho, mfields->U, field->value, nb, mfields->T  );
	break;


    // Li SRT Model
    case 1:
	pseudoPotVelocity( info, mfields->rho, mfields->U, field->value, nb, mfields->T  );
	break;
	
	
    default:
	printf("\n\n[ERROR]  Unable to compute macroscopic velocity with field %s \n\n", field->name);
	exit(1);
	break;	
	
    }

    
}
