#ifndef CAHNHILLIARDFIELD_H
#define CAHNHILLIARDFIELD_H

#include <latticePdfField.h>
#include <latticeScalarField.h>
#include <latticeVectorField.h>


class cahnHilliardField : public latticePdfField {


    /* ----------------------  Protected members ----------------------  */

protected:

    // Reference to external zeroth moment field
    latticeScalarField* _phi;

    // Reference to external first moment field
    latticeVectorField* _U;

    // Reference to chemical potential
    latticeScalarField* _muPhi;    


    // Fluid constants

    double _phi_A;

    double _phi_B;

    // Relaxation parameters
    pdf _diag_S;
    
    // Parameter for mobility control
    double _eta;

    // Parameters for chemical potential
    double _beta;
    double _kappa;

    // Interface width
    double _D;

    // Surface tension
    double _sigma;
    
    


    /* ----------------------  Public members ----------------------  */

public:

    
    // Constructors and destructors

    // Constructor with references
    cahnHilliardField( basicLBModel* lbm, mpi::environment& env, mpi::communicator& world, const std::string& name, const Time& time, const bool& read = true );

    // Default destructor
    ~cahnHilliardField();


    // Link zeroth field
    const void add( latticeScalarField* zerothField );

    // Link first field
    const void add( latticeVectorField* firstField );    

    // Link chemical potential
    const void addChemical( latticeScalarField* chemical );    



    // Access
    
    // Iterator
    #include "cahnHilliardField_iterator.h"

    // Local nodes. Begin
    iterator begin() { return iterator( lbPatch<pdf>::begin(), this, _phi->begin(), _U->begin(), _muPhi->begin() ); }

    // Local nodes. End
    iterator end()   { return iterator( lbPatch<pdf>::end(), this, _phi->end(), _U->end(), _muPhi->end() ); }



    

    // MRT collision matrix
    const Matrix collisionMatrix() const;

    // Source term
    const Matrix sourceMatrix() const;


    // Update zeroth and first moment fields
    const void update();
    
};

#endif // CAHNHILLIARDMRTFIELD_H
