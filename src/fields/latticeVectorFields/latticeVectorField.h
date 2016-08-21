#ifndef LATTICEVECTORFIELD_H
#define LATTICEVECTORFIELD_H

#include <latticeField.h>


class latticeVectorField : public latticeField<Vector3> {


    /* ----------------------  Public members ----------------------  */

public:

    
    // Constructors and destructors

    // Constructor with references
    latticeVectorField( basicLBModel* lbm, mpi::environment& env, mpi::communicator& world, const std::string& name, const Time& time, const bool& read = true );

    // Default destructor
    ~latticeVectorField();


    
    // Access
    
    // Iterator
    #include "latticeVectorField_iterator.h"

    // Local nodes. Begin
    iterator begin() { return iterator( lbPatch<Vector3>::begin(), this); }

    // Local nodes. End
    iterator end()   { return iterator( lbPatch<Vector3>::end(), this); }
    

    
};



#endif // LATTICEVECTORFIELD_H
