#include <stdio.h>
#include <basicSolverInfo.h>
#include <readBasicInfo.h>
#include <readScalarField.h>
#include "fields.h"

int main() {

    // Simulation properties
    struct solverInfo info = readBasicInfo();

    // Read Fields
    struct twoPhaseFields fields;
    
    fields.phi = readScalarField("phi", &info);
    
    return 0;
    
}
