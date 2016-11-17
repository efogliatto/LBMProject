#include <updateBC.h>
#include <string.h>

void updateBC( struct bdInfo* bdElements, int** nb, double** field, char* fname ) {

    unsigned int fid,
	bndId,
	bcId;


    // Select field index an apply BC
    unsigned int i;
    for( i = 0 ; i < bdElements->_nf ; i++ ) {

	if( strcmp(fname, bdElements->_fields[i]) == 0 ) {

	    fid = i;

	}
	
    }


    
    
}
