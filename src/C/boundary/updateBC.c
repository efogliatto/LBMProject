#include <updateBC.h>
#include <string.h>
#include <stdio.h>

void updateBC( struct bdInfo* bdElements, int** nb, double** field, char* fname ) {

    unsigned int fid = 0,
	bndId,
	bcId;


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

	    // bounceBack
	case 0:
	    printf("\n[ERROR]  Unrecognized boundary condition\n\n");

	default:
	    printf("\n[ERROR]  Unrecognized boundary condition\n\n");
	    

	}

    }

    
    
}
