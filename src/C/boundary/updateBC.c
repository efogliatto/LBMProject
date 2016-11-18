#include <updateBC.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void updateBC( struct bdInfo* bdElements, int** nb, double** field, char* fname, struct latticeInfo* lattice, struct macroFields* mfields ) {

    unsigned int fid = 0,
	bndId;


    // Select field index an apply BC
    unsigned int i;
    for( i = 0 ; i < bdElements->_nf ; i++ ) {

	if( strcmp(fname, bdElements->_fields[i]) == 0 ) {

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
	    bounceBack( bdElements, nb, field, bndId, lattice );
	    break;

        // fixedT
	case 4:
	    printf("\n[ERROR]  Unrecognized boundary condition\n\n");
	    break;
	    
	default:
	    printf("\n[ERROR]  Unrecognized boundary condition\n\n");
	    exit(1);
	    

	}

    }

    
    
}
