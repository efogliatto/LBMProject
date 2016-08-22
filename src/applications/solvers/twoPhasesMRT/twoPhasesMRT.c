#include <stdio.h>
#include <basicSolverInfo.h>
#include <readBasicInfo.h>
#include <readScalarField.h>
#include <twoPhasesFields.h>

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
    
    return 0;
    
}
