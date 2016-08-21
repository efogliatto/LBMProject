#ifndef LATTICESCALARFIELD_H
#define LATTICESCALARFIELD_H

#include <latticeField.h>
/* #include <latticeScalarField_iterator.h> */

/* class latticeScalarField_iterator; */


class latticeScalarField : public latticeField<double> {


    /* ----------------------  Public members ----------------------  */

public:

    
    // Constructors and destructors

    // Constructor with references
    latticeScalarField( basicLBModel* lbm, mpi::environment& env, mpi::communicator& world, const std::string& name, const Time& time, const bool& read = true  );

    // Default destructor
    ~latticeScalarField();


    
    // Access
    
    // Iterator
    #include "latticeScalarField_iterator.h"

    // Local nodes. Begin
    iterator begin() { return iterator( lbPatch<double>::begin(), this); }

    // Local nodes. End
    iterator end()   { return iterator( lbPatch<double>::end(), this); }
    

    
};



#endif // LATTICESCALARFIELD_H
