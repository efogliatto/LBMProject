#include <updateBoundaries.h>
#include <stdlib.h>
#include <string.h>

void updateBoundaries( struct bdInfo* bdElements, struct lbeField* field, struct latticeInfo* lattice, struct macroFields* mfields, int** nb ) {

    unsigned int fid = 0,
	bndId;


    // Select field index an apply BC
    unsigned int i;
    for( i = 0 ; i < bdElements->_nf ; i++ ) {

	if( strcmp(field->name, bdElements->_fields[i]) == 0 ) {

	    fid = i;

	}
	
    }


    
    // Move over boundaries and apply condition
    
    for( bndId = 0 ; bndId < bdElements->_nb ; bndId++ ) {

	switch( bdElements->_bc[fid][bndId] ) {

        // none - periodic
	case 0:
	    break;
	    
        // bounceBack
	case 1:
	    bounceBack( bdElements, field, lattice, nb, bndId );
	    break;

        // fixedT
	case 4:
	    fixedT( bdElements, field, lattice, mfields, nb, fid, bndId );
	    break;

        // adiabatic
	case 5:
	    /* adiabatic( bdElements, nb, field->value, bndId, lattice, mfields, fid ); */
	    break;
	    
	default:
	    printf("\n[ERROR]  Unrecognized boundary condition \n\n\n");
	    exit(1);
	    

	}

    }

    
}
