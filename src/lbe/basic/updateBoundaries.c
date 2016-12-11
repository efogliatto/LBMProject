#include <updateBoundaries.h>
#include <stdlib.h>
#include <string.h>

void updateBoundaries( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {

    unsigned int fid = 0,
	bndId;


    // Select field index an apply BC
    unsigned int i;
    for( i = 0 ; i < mesh->bdElements._nf ; i++ ) {

	if( strcmp(field->name, mesh->bdElements._fields[i]) == 0 ) {

	    fid = i;

	}
	
    }


    
    // Move over boundaries and apply condition
    
    for( bndId = 0 ; bndId < mesh->bdElements._nb ; bndId++ ) {

	switch( mesh->bdElements._bc[fid][bndId] ) {

        // none - periodic
	case 0:
	    break;
	    
        // bounceBack
	case 1:
	    bounceBack( &mesh->bdElements, field, &mesh->lattice, mesh->nb, bndId, mfields );
	    break;

        // fixedU
	case 2:
	    fixedU( &mesh->bdElements, field, &mesh->lattice, mfields, mesh->nb, fid, bndId );
	    break;
	    
        // fixedT
	case 4:
	    fixedT( &mesh->bdElements, field, &mesh->lattice, mfields, mesh->nb, fid, bndId );
	    break;

        // adiabatic
	case 5:
	    adiabatic( &mesh->bdElements, field, &mesh->lattice, mfields, mesh->nb, fid, bndId );
	    break;
	
        // randomT
	case 6:
	    randomT( &mesh->bdElements, field, &mesh->lattice, mfields, mesh->nb, fid, bndId );
	    break;

        // tSpot
	case 7:
	    tSpot( &mesh->bdElements, field, &mesh->lattice, mfields, mesh->nb, fid, bndId );
	    break;
    
	default:
	    printf("\n[ERROR]  Unrecognized boundary condition \n\n\n");
	    exit(1);
	    

	}

    }

    
}
