#include <stdio.h>
#include <basicSolverInfo.h>
#include <readBasicInfo.h>
#include <readScalarField.h>
#include <readVectorField.h>
#include <readPdfField.h>
#include <twoPhasesFields.h>
#include <cahnHilliardCollision.h>
#include <liangCollision.h>
#include <timeOptions.h>


int main() {

    double lap = 0;
    
    // Simulation properties
    struct solverInfo info = readBasicInfo();


    
    // Read Fields
    struct twoPhasesFields fields;

    // Neighbours indices
    fields.nb = readNeighbours(&info);
    
    // Order parameter
    fields.phi     = readScalarField("phi", &info);
    fields.phi_old = readScalarField("phi", &info);

    // Chemical potential
    fields.muPhi = readScalarField("muPhi", &info);

    // Pressure
    fields.p = readScalarField("p", &info);

    // Density
    fields.rho = readScalarField("rho", &info);

    // Velocity
    fields.U     = readVectorField("U", &info);
    fields.U_old = readVectorField("U", &info);

    // Cahn-Hilliard field
    fields.h = readPdfField("h", &info);

    // Navier-Stokes field
    fields.g = readPdfField("g", &info);
    fields.swp = readPdfField("g", &info);
    



    // Advance in time. Collide, stream, update and write
    while( updateTime(&info) ) {

	
    	// Collide h
    	cahnHilliardCollision(&fields, &info);

    	// Collide g
    	liangCollision(&fields, &info);


	// Swap fields
	swap( &fields, &info, fields.h );
	swap( &fields, &info, fields.g );
	

    	// Write fields
    	if( writeFlag(&info) ) {
	    
    	    // ScalarFields
    	    writeScalarField("phi", fields.phi, &info);
    	    writeScalarField("muPhi", fields.muPhi, &info);
    	    writeScalarField("rho", fields.rho, &info);
    	    writeScalarField("p", fields.p, &info);

    	    // Vector fields
    	    writeVectorField("U", fields.U, &info);

    	    // Pdf fields
    	    writePdfField("h", fields.h, &info);
    	    writePdfField("g", fields.g, &info);
	    
    	}

    }


    
    // Print info
    double rt = elapsed(&info);
    printf("\n Finished in %.2f = seconds \n\n", rt );
    
    return 0;
    
}
