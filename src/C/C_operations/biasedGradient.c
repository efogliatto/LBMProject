#include <biasedGradient.h>
#include <stdlib.h>

c_scalar* biasedGradient( c_scalar* fld, int** nb, c_scalar** vel, int pdir[3][2], double lsize, int id ) {

    c_scalar* grad = (c_scalar*)malloc( 3 * sizeof(c_scalar));
    grad[0] = 0;
    grad[1] = 0;
    grad[2] = 0;

    // Move over directions
    unsigned int dir;

    for( dir = 0 ; dir < 3 ; dir++ ) {
	    
    	if( vel[id][dir] >= 0 ) {
	    
    	    int nid = nb[id][ pdir[dir][0] ];

    	    if( nid != -1 ) {
	    
    		grad[dir] = (1/lsize) * ( fld[nid] - fld[id] );

    	    }
	    
    	}
	
    	else {

    	    int nid = nb[id][ pdir[dir][1] ];

    	    if( nid != -1 ) {
	    
    		grad[dir] = (1/lsize) * ( fld[id] - fld[nid] );

    	    }
	    
    	}

    }
    
    

    return grad;
    
}
