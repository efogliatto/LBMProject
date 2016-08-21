#include <stdio.h>
#include "data.h"

struct Time readTime();
struct lattice readLatticeProperties();
struct fields readFieldsProperties();
double* readScalarField(const char* fname, const struct Time t, const struct lattice lat);
double** readVectorField(const char* fname, const struct Time t, const struct lattice lat);
double** readPdfField(const char* fname, const struct Time t, const struct lattice lat);
int** readNeighbours(const struct lattice lat);
void collideCahnHilliard(double* phi,double* muPhi,double** U,double** h, const struct lattice lat);


int main() {

    // Simulation properties
    
    struct Time t;
    t = readTime();

    struct lattice lat;
    lat = readLatticeProperties();

    struct fields fld;
    fld = readFieldsProperties();


    // Simulation fields

    // Order parameter
    double* phi;
    phi = readScalarField("phi", t, lat);
    
    // Chemical potential
    double* muPhi;
    muPhi = readScalarField("muPhi", t, lat);

    // Pressure
    double* p;
    p = readScalarField("p", t, lat);

    // Density
    double* rho;
    rho = readScalarField("rho", t, lat);

    // Velocity
    double** U;
    U = readVectorField("U", t, lat);    

    // Cahn-Hilliard field
    double** h;
    h = readPdfField("h", t, lat);

    // Momentum field
    double** g;
    g = readPdfField("g", t, lat);

    // Neighbours indices
    int** nb;
    nb = readNeighbours(lat);



    // Move over time. Collide, stream and update fields
    while(t.current <= t.end) {

	// Update time
	t.current += t.tstep;

	// Collide Cahn-Hilliard Field
	collideCahnHilliard(phi,muPhi,U,h,lat);
	
    };
    
    return 0;
    
}
