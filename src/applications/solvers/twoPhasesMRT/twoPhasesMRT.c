#include <stdio.h>
#include <basicSolverInfo.h>
#include <readBasicInfo.h>
#include <readScalarField.h>
#include <readVectorField.h>
#include <readPdfField.h>
#include <twoPhasesFields.h>
#include <cahnHilliardCollision.h>

int main() {

    // Simulation properties
    struct solverInfo info = readBasicInfo();


    
    // Read Fields
    struct twoPhasesFields fields;

    // Order parameter
    fields.phi = readScalarField("phi", &info);

    // Chemical potential
    fields.muPhi = readScalarField("muPhi", &info);

    // Pressure
    fields.p = readScalarField("p", &info);

    // Density
    fields.rho = readScalarField("rho", &info);

    // Velocity
    fields.U = readVectorField("U", &info);

    // Cahn-Hilliard field
    fields.h = readPdfField("h", &info);

    // Navier-Stokes field
    fields.g = readPdfField("g", &info);    



    // Advance in time. Collide, stream, update and write
    while(info.time.current < info.time.end) {

    	// Update time
    	info.time.current += info.time.tstep;

	printf("time = %.2f \n", info.time.current);

	// Collide h
	cahnHilliardCollision(&fields, &info);

    }
    
    return 0;
    
}
