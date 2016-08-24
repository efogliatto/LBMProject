#include <stdio.h>
#include <basicSolverInfo.h>
#include <readBasicInfo.h>
#include <readScalarField.h>
#include <readVectorField.h>
#include <readPdfField.h>
#include <twoPhasesFields.h>
#include <cahnHilliardCollision.h>
#include <liangCollision.h>


int main() {

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



    // Advance in time. Collide, stream, update and write
    while( updateTime(&info) ) {

	// Collide h
	cahnHilliardCollision(&fields, &info);

	// Collide g
	liangCollision(&fields, &info);	

    }


    // Print info
    double rt = elapsed(&info);
    printf("\n Finished in %.0f = seconds \n", rt );
    
    return 0;
    
}
