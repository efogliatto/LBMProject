#include <chemicalPotential.h>
#include <syncScalarField.h>

void chemicalPotential( struct twoPhasesFields* fields, struct solverInfo* info, c_scalar* chfield ) {

    unsigned int id;

    // Move over points
    for( id = 0 ; id < info->lattice.nlocal ; id++ ) {
	chfield[id] = 4 * info->fields.beta * ( fields->phi[id] - info->fields.phi_A) * ( fields->phi[id] - info->fields.phi_B) * ( fields->phi[id] - ( (info->fields.phi_A + info->fields.phi_B) / 2) )   -  info->fields.kappa * scalarFieldLaplacian(fields, info, fields->phi, id);
    }

    
    // Sync field
    syncScalarField( &info->parallel, chfield );
    
}
