#include <collision.h>
#include <liSRTCollision.h>
#include <temperatureCollision.h>
#include <pseudoPotCollision.h>
#include <stdlib.h>

void collision( struct liModelInfo* info, struct macroFields* mfields, struct lbeField* field, int** nb ) {


    // Apply collision model
    switch(field->colId) {

    // Li MRT Model
    case 0:
	pseudoPotCollision( info, mfields->T, mfields->rho, mfields->U, nb, field->value );
	break;


    // Li SRT Model
    case 1:
	liSRTCollision(info, mfields, field, nb);
	break;

	
    // Li SRT Model. Temperature
    case 2:
	temperatureCollision( info, mfields->T, mfields->rho, mfields->U, nb, field->value );
	break;
	
	
    default:
	printf("\n\n[ERROR]  Collision model is not yet implemented\n\n");
	exit(1);
	break;	
	
    }
    

};
