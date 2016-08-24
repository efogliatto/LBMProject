#ifndef LIANGFIELD_H
#define LIANGFIELD_H

#include <latticePdfField.h>
#include <latticeScalarField.h>
#include <latticeVectorField.h>

class liangField : public latticePdfField {

    
    /* ----------------------  Protected members ----------------------  */

protected:


    // Reference to external zeroth moment field
    latticeScalarField* _p;

    // Reference to external first moment field
    latticeVectorField* _U;

    // Reference to chemical potential
    latticeScalarField* _muPhi;

    // Reference to order parameter
    latticeScalarField* _phi;

    // Reference to density
    latticeScalarField* _rho;          


    
    // Fluid constants

    double _phi_A;

    double _phi_B;

    double _rho_A;

    double _rho_B;

    // Relaxation parameters
    pdf _diag_S_a;
    pdf _diag_S_b;
    
    // Mobility
    double _M;

    // Body Force
    Vector3 _G;

    
    /* ----------------------  Public members ----------------------  */

public:

    
    // Constructors and destructors

    // Constructor with references
    liangField( basicLBModel* lbm, mpi::environment& env, mpi::communicator& world, const std::string& name, const Time& time, const bool& read = true );

    // Default destructor
    ~liangField();    



    // Link scalars field
    const void add( latticeScalarField* scfield );

    // Link vector field
    const void add( latticeVectorField* vfield );
    

    
    // Access
    
    // Iterator
    #include "liangField_iterator.h"

    // Local nodes. Begin
    iterator begin() { return iterator( lbPatch<pdf>::begin(), this, _phi->begin(), _U->begin(), _muPhi->begin(), _p->begin(), _rho->begin() ); }

    // Local nodes. End
    iterator end()   { return iterator( lbPatch<pdf>::end(), this, _phi->end(), _U->end(), _muPhi->end(), _p->end(), _rho->end() ); }


    

    // MRT collision matrix
    const Matrix collisionMatrixA() const;
    const Matrix collisionMatrixB() const;

    // Source term
    const Matrix sourceMatrixA() const;
    const Matrix sourceMatrixB() const;


    // Update zeroth and first moment fields
    const void update();


    
};

#endif // LIANGFIELD_H
